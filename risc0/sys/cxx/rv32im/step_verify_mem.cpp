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
namespace risc0::circuit::rv32im {

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif

Fp step_verify_mem(void* ctx, HostBridge host, size_t steps, size_t cycle, Fp** args) {
  size_t mask = steps - 1;
  std::array<Fp, 32> host_args;
  std::array<Fp, 32> host_outs;
  // loc("cirgen/components/ram.cpp":23:14)
  Fp x0(33554431);
  // loc("cirgen/components/ram.cpp":22:13)
  Fp x1(67108863);
  // loc("cirgen/circuit/rv32im/body.cpp":17:32)
  Fp x2(3);
  // loc("cirgen/components/bytes.cpp":90:30)
  Fp x3(2005401601);
  // loc("cirgen/components/bytes.cpp":89:26)
  Fp x4(255);
  // loc("cirgen/components/bytes.cpp":37:25)
  Fp x5(2);
  // loc("cirgen/components/bytes.cpp":21:13)
  Fp x6(0);
  // loc("cirgen/circuit/rv32im/top.cpp":18:17)
  Fp x7(1);
  // loc("Top/Code/OneHot/hot[1](Reg)"("./cirgen/components/mux.h":39:25))
  auto x8 = args[0][2 * steps + ((cycle - 0) & mask)];
  assert(x8 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[2](Reg)"("./cirgen/components/mux.h":39:25))
  auto x9 = args[0][3 * steps + ((cycle - 0) & mask)];
  assert(x9 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[3](Reg)"("./cirgen/components/mux.h":39:25))
  auto x10 = args[0][4 * steps + ((cycle - 0) & mask)];
  assert(x10 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[4](Reg)"("./cirgen/components/mux.h":39:25))
  auto x11 = args[0][5 * steps + ((cycle - 0) & mask)];
  assert(x11 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[5](Reg)"("./cirgen/components/mux.h":39:25))
  auto x12 = args[0][6 * steps + ((cycle - 0) & mask)];
  assert(x12 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[0](Reg)"("cirgen/circuit/rv32im/top.cpp":71:27))
  auto x13 = args[0][1 * steps + ((cycle - 0) & mask)];
  assert(x13 != Fp::invalid());
  if (x13 != 0) {
    // loc("cirgen/components/ram.cpp":15:3)
    {
      auto& reg = args[2][2 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("cirgen/components/ram.cpp":16:3)
    {
      auto& reg = args[2][3 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("cirgen/components/ram.cpp":17:3)
    {
      auto& reg = args[2][4 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("cirgen/components/u32.cpp":28:5)
    {
      auto& reg = args[2][5 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("cirgen/components/u32.cpp":28:5)
    {
      auto& reg = args[2][6 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("cirgen/components/u32.cpp":28:5)
    {
      auto& reg = args[2][7 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("cirgen/components/u32.cpp":28:5)
    {
      auto& reg = args[2][8 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
  }
  if (x8 != 0) {
    // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x14 = args[2][2 * steps + ((cycle - 1) & mask)];
    assert(x14 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x15 = args[2][3 * steps + ((cycle - 1) & mask)];
    assert(x15 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x16 = args[2][4 * steps + ((cycle - 1) & mask)];
    assert(x16 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x17 = args[2][5 * steps + ((cycle - 1) & mask)];
    assert(x17 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x18 = args[2][6 * steps + ((cycle - 1) & mask)];
    assert(x18 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x19 = args[2][7 * steps + ((cycle - 1) & mask)];
    assert(x19 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x20 = args[2][8 * steps + ((cycle - 1) & mask)];
    assert(x20 != Fp::invalid());
    // loc("cirgen/components/ram.cpp":36:3)
    {
      auto& reg = args[2][2 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x14);
      reg = x14;
    }
    // loc("cirgen/components/ram.cpp":37:3)
    {
      auto& reg = args[2][3 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x15);
      reg = x15;
    }
    // loc("cirgen/components/ram.cpp":38:3)
    {
      auto& reg = args[2][4 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x16);
      reg = x16;
    }
    // loc("cirgen/components/u32.cpp":82:5)
    {
      auto& reg = args[2][5 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x17);
      reg = x17;
    }
    // loc("cirgen/components/u32.cpp":82:5)
    {
      auto& reg = args[2][6 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x18);
      reg = x18;
    }
    // loc("cirgen/components/u32.cpp":82:5)
    {
      auto& reg = args[2][7 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x19);
      reg = x19;
    }
    // loc("cirgen/components/u32.cpp":82:5)
    {
      auto& reg = args[2][8 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x20);
      reg = x20;
    }
  }
  if (x9 != 0) {
    {
      host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
      auto x21 = host_outs.at(0);
      auto x22 = host_outs.at(1);
      auto x23 = host_outs.at(2);
      auto x24 = host_outs.at(3);
      auto x25 = host_outs.at(4);
      auto x26 = host_outs.at(5);
      auto x27 = host_outs.at(6);
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][136 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x21);
        reg = x21;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][137 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x22);
        reg = x22;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][138 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x23);
        reg = x23;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][139 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x24);
        reg = x24;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][140 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x25);
        reg = x25;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][141 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x26);
        reg = x26;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][142 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x27);
        reg = x27;
      }
      host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
      auto x28 = host_outs.at(0);
      auto x29 = host_outs.at(1);
      auto x30 = host_outs.at(2);
      auto x31 = host_outs.at(3);
      auto x32 = host_outs.at(4);
      auto x33 = host_outs.at(5);
      auto x34 = host_outs.at(6);
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][143 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x28);
        reg = x28;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][144 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x29);
        reg = x29;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][145 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x30);
        reg = x30;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][146 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x31);
        reg = x31;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][147 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x32);
        reg = x32;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][148 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x33);
        reg = x33;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][149 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x34);
        reg = x34;
      }
      host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
      auto x35 = host_outs.at(0);
      auto x36 = host_outs.at(1);
      auto x37 = host_outs.at(2);
      auto x38 = host_outs.at(3);
      auto x39 = host_outs.at(4);
      auto x40 = host_outs.at(5);
      auto x41 = host_outs.at(6);
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][150 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x35);
        reg = x35;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][151 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x36);
        reg = x36;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][152 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x37);
        reg = x37;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][153 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x38);
        reg = x38;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][154 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x39);
        reg = x39;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][155 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x40);
        reg = x40;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][156 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x41);
        reg = x41;
      }
      host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
      auto x42 = host_outs.at(0);
      auto x43 = host_outs.at(1);
      auto x44 = host_outs.at(2);
      auto x45 = host_outs.at(3);
      auto x46 = host_outs.at(4);
      auto x47 = host_outs.at(5);
      auto x48 = host_outs.at(6);
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x42);
        reg = x42;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x43);
        reg = x43;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x44);
        reg = x44;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x45);
        reg = x45;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x46);
        reg = x46;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x47);
        reg = x47;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x48);
        reg = x48;
      }
    }
    // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
    auto x49 = args[2][2 * steps + ((cycle - 1) & mask)];
    assert(x49 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
    auto x50 = args[2][3 * steps + ((cycle - 1) & mask)];
    assert(x50 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
    auto x51 = args[2][4 * steps + ((cycle - 1) & mask)];
    assert(x51 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x52 = args[2][5 * steps + ((cycle - 1) & mask)];
    assert(x52 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x53 = args[2][6 * steps + ((cycle - 1) & mask)];
    assert(x53 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x54 = args[2][7 * steps + ((cycle - 1) & mask)];
    assert(x54 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x55 = args[2][8 * steps + ((cycle - 1) & mask)];
    assert(x55 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x56 = args[2][139 * steps + ((cycle - 0) & mask)];
    assert(x56 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x57 = args[2][140 * steps + ((cycle - 0) & mask)];
    assert(x57 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x58 = args[2][141 * steps + ((cycle - 0) & mask)];
    assert(x58 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x59 = args[2][142 * steps + ((cycle - 0) & mask)];
    assert(x59 != Fp::invalid());
    {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x60 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x60 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x61 = x49 - x60;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x62 = (x61 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x63 = x7 - x62;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][157 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x63);
        reg = x63;
      }
    }
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x64 = args[2][157 * steps + ((cycle - 0) & mask)];
    assert(x64 != Fp::invalid());
    if (x64 != 0) {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x65 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x65 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x66 = x6 - x65;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x66 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x67 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x67 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x68 = x67 - x49;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x69 = x68 - x7;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x70 = Fp(x69.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][10 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x70);
          reg = x70;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x71 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x71 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x72 = x69 - x71;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x73 = x72 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x74 = Fp(x73.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][11 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x74);
          reg = x74;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x75 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x75 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x76 = x73 - x75;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x77 = x76 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x78 = Fp(x77.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][12 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x78);
          reg = x78;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x79 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x79 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x80 = x77 - x79;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x81 = x80 * x3;
      // loc("./cirgen/components/bits.h":61:23)
      {
        auto& reg = args[2][72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x81);
        reg = x81;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x82 = x7 - x64;
    if (x82 != 0) {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x83 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x83 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x84 = x7 - x83;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x85 = x5 - x83;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x86 = x84 * x85;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x86 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x87 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x87 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x88 = x49 - x87;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x88 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x89 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x89 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x90 = x89 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x91 = x90 + x83;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x92 = x50 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x93 = x91 - x92;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x94 = x93 + x51;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x95 = Fp(x94.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][10 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x95);
          reg = x95;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x96 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x96 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x97 = x94 - x96;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x98 = x97 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x99 = Fp(x98.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][11 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x99);
          reg = x99;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x100 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x100 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x101 = x98 - x100;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x102 = x101 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x103 = Fp(x102.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][12 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x103);
          reg = x103;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x104 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x104 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x105 = x102 - x104;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x106 = x105 * x3;
      // loc("./cirgen/components/bits.h":61:23)
      {
        auto& reg = args[2][72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x106);
        reg = x106;
      }
      if (x85 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x107 = x52 - x56;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x107 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x108 = x53 - x57;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x108 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x109 = x54 - x58;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x109 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x110 = x55 - x59;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x110 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
    auto x111 = args[2][136 * steps + ((cycle - 0) & mask)];
    assert(x111 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
    auto x112 = args[2][137 * steps + ((cycle - 0) & mask)];
    assert(x112 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
    auto x113 = args[2][138 * steps + ((cycle - 0) & mask)];
    assert(x113 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x114 = args[2][146 * steps + ((cycle - 0) & mask)];
    assert(x114 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x115 = args[2][147 * steps + ((cycle - 0) & mask)];
    assert(x115 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x116 = args[2][148 * steps + ((cycle - 0) & mask)];
    assert(x116 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x117 = args[2][149 * steps + ((cycle - 0) & mask)];
    assert(x117 != Fp::invalid());
    {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x118 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x118 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x119 = x111 - x118;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x120 = (x119 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x121 = x7 - x120;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][158 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x121);
        reg = x121;
      }
    }
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x122 = args[2][158 * steps + ((cycle - 0) & mask)];
    assert(x122 != Fp::invalid());
    if (x122 != 0) {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x123 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x123 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x124 = x6 - x123;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x124 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x125 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x125 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x126 = x125 - x111;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x127 = x126 - x7;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x128 = Fp(x127.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][13 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x128);
          reg = x128;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x129 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x129 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x130 = x127 - x129;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x131 = x130 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x132 = Fp(x131.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][14 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x132);
          reg = x132;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x133 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x133 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x134 = x131 - x133;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x135 = x134 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x136 = Fp(x135.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][15 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x136);
          reg = x136;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x137 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x137 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x138 = x135 - x137;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x139 = x138 * x3;
      // loc("./cirgen/components/bits.h":61:23)
      {
        auto& reg = args[2][73 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x139);
        reg = x139;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x140 = x7 - x122;
    if (x140 != 0) {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x141 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x141 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x142 = x7 - x141;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x143 = x5 - x141;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x144 = x142 * x143;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x144 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x145 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x145 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x146 = x111 - x145;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x146 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x147 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x147 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x148 = x147 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x149 = x148 + x141;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x150 = x112 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x151 = x149 - x150;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x152 = x151 + x113;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x153 = Fp(x152.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][13 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x153);
          reg = x153;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x154 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x154 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x155 = x152 - x154;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x156 = x155 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x157 = Fp(x156.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][14 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x157);
          reg = x157;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x158 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x158 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x159 = x156 - x158;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x160 = x159 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x161 = Fp(x160.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][15 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x161);
          reg = x161;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x162 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x162 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x163 = x160 - x162;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x164 = x163 * x3;
      // loc("./cirgen/components/bits.h":61:23)
      {
        auto& reg = args[2][73 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x164);
        reg = x164;
      }
      if (x143 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x165 = x56 - x114;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x165 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x166 = x57 - x115;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x166 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x167 = x58 - x116;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x167 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x168 = x59 - x117;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x168 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
    auto x169 = args[2][143 * steps + ((cycle - 0) & mask)];
    assert(x169 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
    auto x170 = args[2][144 * steps + ((cycle - 0) & mask)];
    assert(x170 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
    auto x171 = args[2][145 * steps + ((cycle - 0) & mask)];
    assert(x171 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x172 = args[2][153 * steps + ((cycle - 0) & mask)];
    assert(x172 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x173 = args[2][154 * steps + ((cycle - 0) & mask)];
    assert(x173 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x174 = args[2][155 * steps + ((cycle - 0) & mask)];
    assert(x174 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x175 = args[2][156 * steps + ((cycle - 0) & mask)];
    assert(x175 != Fp::invalid());
    {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x176 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x176 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x177 = x169 - x176;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x178 = (x177 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x179 = x7 - x178;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][159 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x179);
        reg = x179;
      }
    }
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x180 = args[2][159 * steps + ((cycle - 0) & mask)];
    assert(x180 != Fp::invalid());
    if (x180 != 0) {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x181 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x181 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x182 = x6 - x181;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x182 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x183 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x183 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x184 = x183 - x169;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x185 = x184 - x7;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x186 = Fp(x185.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][16 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x186);
          reg = x186;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x187 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x187 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x188 = x185 - x187;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x189 = x188 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x190 = Fp(x189.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][17 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x190);
          reg = x190;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x191 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x191 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x192 = x189 - x191;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x193 = x192 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x194 = Fp(x193.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][18 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x194);
          reg = x194;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x195 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x195 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x196 = x193 - x195;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x197 = x196 * x3;
      // loc("./cirgen/components/bits.h":61:23)
      {
        auto& reg = args[2][74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x197);
        reg = x197;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x198 = x7 - x180;
    if (x198 != 0) {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x199 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x199 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x200 = x7 - x199;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x201 = x5 - x199;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x202 = x200 * x201;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x202 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x203 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x203 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x204 = x169 - x203;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x204 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x205 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x205 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x206 = x205 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x207 = x206 + x199;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x208 = x170 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x209 = x207 - x208;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x210 = x209 + x171;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x211 = Fp(x210.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][16 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x211);
          reg = x211;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x212 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x212 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x213 = x210 - x212;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x214 = x213 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x215 = Fp(x214.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][17 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x215);
          reg = x215;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x216 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x216 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x217 = x214 - x216;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x218 = x217 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x219 = Fp(x218.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][18 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x219);
          reg = x219;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x220 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x220 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x221 = x218 - x220;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x222 = x221 * x3;
      // loc("./cirgen/components/bits.h":61:23)
      {
        auto& reg = args[2][74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x222);
        reg = x222;
      }
      if (x201 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x223 = x114 - x172;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x223 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x224 = x115 - x173;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x224 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x225 = x116 - x174;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x225 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x226 = x117 - x175;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x226 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
    auto x227 = args[2][150 * steps + ((cycle - 0) & mask)];
    assert(x227 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
    auto x228 = args[2][151 * steps + ((cycle - 0) & mask)];
    assert(x228 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
    auto x229 = args[2][152 * steps + ((cycle - 0) & mask)];
    assert(x229 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x230 = args[2][5 * steps + ((cycle - 0) & mask)];
    assert(x230 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x231 = args[2][6 * steps + ((cycle - 0) & mask)];
    assert(x231 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x232 = args[2][7 * steps + ((cycle - 0) & mask)];
    assert(x232 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x233 = args[2][8 * steps + ((cycle - 0) & mask)];
    assert(x233 != Fp::invalid());
    {
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x234 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x234 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x235 = x227 - x234;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x236 = (x235 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x237 = x7 - x236;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][160 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x237);
        reg = x237;
      }
    }
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x238 = args[2][160 * steps + ((cycle - 0) & mask)];
    assert(x238 != Fp::invalid());
    if (x238 != 0) {
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x239 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x239 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x240 = x6 - x239;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x240 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x241 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x241 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x242 = x241 - x227;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x243 = x242 - x7;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x244 = Fp(x243.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][19 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x244);
          reg = x244;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x245 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x245 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x246 = x243 - x245;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x247 = x246 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x248 = Fp(x247.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][20 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x248);
          reg = x248;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x249 = args[2][20 * steps + ((cycle - 0) & mask)];
      assert(x249 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x250 = x247 - x249;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x251 = x250 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x252 = Fp(x251.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x252);
          reg = x252;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x253 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x253 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x254 = x251 - x253;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x255 = x254 * x3;
      // loc("./cirgen/components/bits.h":61:23)
      {
        auto& reg = args[2][75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x255);
        reg = x255;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x256 = x7 - x238;
    if (x256 != 0) {
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x257 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x257 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x258 = x7 - x257;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x259 = x5 - x257;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x260 = x258 * x259;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x260 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x261 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x261 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x262 = x227 - x261;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x262 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x263 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x263 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x264 = x263 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x265 = x264 + x257;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x266 = x228 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x267 = x265 - x266;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x268 = x267 + x229;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x269 = Fp(x268.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][19 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x269);
          reg = x269;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x270 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x270 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x271 = x268 - x270;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x272 = x271 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x273 = Fp(x272.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][20 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x273);
          reg = x273;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x274 = args[2][20 * steps + ((cycle - 0) & mask)];
      assert(x274 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x275 = x272 - x274;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x276 = x275 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x277 = Fp(x276.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x277);
          reg = x277;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x278 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x278 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x279 = x276 - x278;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x280 = x279 * x3;
      // loc("./cirgen/components/bits.h":61:23)
      {
        auto& reg = args[2][75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x280);
        reg = x280;
      }
      if (x259 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x281 = x172 - x230;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x281 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x282 = x173 - x231;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x282 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x283 = x174 - x232;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x283 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x284 = x175 - x233;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x284 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
  }
  if (x10 != 0) {
    {
      host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
      auto x285 = host_outs.at(0);
      auto x286 = host_outs.at(1);
      auto x287 = host_outs.at(2);
      auto x288 = host_outs.at(3);
      auto x289 = host_outs.at(4);
      auto x290 = host_outs.at(5);
      auto x291 = host_outs.at(6);
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][136 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x285);
        reg = x285;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][137 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x286);
        reg = x286;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][138 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x287);
        reg = x287;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][139 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x288);
        reg = x288;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][140 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x289);
        reg = x289;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][141 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x290);
        reg = x290;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][142 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x291);
        reg = x291;
      }
      host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
      auto x292 = host_outs.at(0);
      auto x293 = host_outs.at(1);
      auto x294 = host_outs.at(2);
      auto x295 = host_outs.at(3);
      auto x296 = host_outs.at(4);
      auto x297 = host_outs.at(5);
      auto x298 = host_outs.at(6);
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][143 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x292);
        reg = x292;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][144 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x293);
        reg = x293;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][145 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x294);
        reg = x294;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][146 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x295);
        reg = x295;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][147 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x296);
        reg = x296;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][148 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x297);
        reg = x297;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][149 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x298);
        reg = x298;
      }
      host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
      auto x299 = host_outs.at(0);
      auto x300 = host_outs.at(1);
      auto x301 = host_outs.at(2);
      auto x302 = host_outs.at(3);
      auto x303 = host_outs.at(4);
      auto x304 = host_outs.at(5);
      auto x305 = host_outs.at(6);
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][150 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x299);
        reg = x299;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][151 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x300);
        reg = x300;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][152 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x301);
        reg = x301;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][153 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x302);
        reg = x302;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][154 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x303);
        reg = x303;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][155 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x304);
        reg = x304;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][156 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x305);
        reg = x305;
      }
      host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
      auto x306 = host_outs.at(0);
      auto x307 = host_outs.at(1);
      auto x308 = host_outs.at(2);
      auto x309 = host_outs.at(3);
      auto x310 = host_outs.at(4);
      auto x311 = host_outs.at(5);
      auto x312 = host_outs.at(6);
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x306);
        reg = x306;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x307);
        reg = x307;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x308);
        reg = x308;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x309);
        reg = x309;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x310);
        reg = x310;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x311);
        reg = x311;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x312);
        reg = x312;
      }
    }
    // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
    auto x313 = args[2][2 * steps + ((cycle - 1) & mask)];
    assert(x313 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
    auto x314 = args[2][3 * steps + ((cycle - 1) & mask)];
    assert(x314 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
    auto x315 = args[2][4 * steps + ((cycle - 1) & mask)];
    assert(x315 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x316 = args[2][5 * steps + ((cycle - 1) & mask)];
    assert(x316 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x317 = args[2][6 * steps + ((cycle - 1) & mask)];
    assert(x317 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x318 = args[2][7 * steps + ((cycle - 1) & mask)];
    assert(x318 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x319 = args[2][8 * steps + ((cycle - 1) & mask)];
    assert(x319 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x320 = args[2][139 * steps + ((cycle - 0) & mask)];
    assert(x320 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x321 = args[2][140 * steps + ((cycle - 0) & mask)];
    assert(x321 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x322 = args[2][141 * steps + ((cycle - 0) & mask)];
    assert(x322 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x323 = args[2][142 * steps + ((cycle - 0) & mask)];
    assert(x323 != Fp::invalid());
    {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x324 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x324 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x325 = x313 - x324;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x326 = (x325 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x327 = x7 - x326;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][157 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x327);
        reg = x327;
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x328 = args[2][157 * steps + ((cycle - 0) & mask)];
    assert(x328 != Fp::invalid());
    if (x328 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x329 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x329 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x330 = x6 - x329;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x330 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x331 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x331 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x332 = x331 - x313;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x333 = x332 - x7;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x334 = Fp(x333.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][13 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x334);
          reg = x334;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x335 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x335 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x336 = x333 - x335;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x337 = x336 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x338 = Fp(x337.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][14 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x338);
          reg = x338;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x339 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x339 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x340 = x337 - x339;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x341 = x340 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x342 = Fp(x341.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][15 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x342);
          reg = x342;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x343 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x343 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x344 = x341 - x343;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x345 = x344 * x3;
      // loc("./cirgen/components/bits.h":61:23)
      {
        auto& reg = args[2][74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x345);
        reg = x345;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x346 = x7 - x328;
    if (x346 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x347 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x347 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x348 = x7 - x347;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x349 = x5 - x347;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x350 = x348 * x349;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x350 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x351 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x351 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x352 = x313 - x351;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x352 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x353 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x353 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x354 = x353 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x355 = x354 + x347;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x356 = x314 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x357 = x355 - x356;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x358 = x357 + x315;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x359 = Fp(x358.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][13 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x359);
          reg = x359;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x360 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x360 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x361 = x358 - x360;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x362 = x361 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x363 = Fp(x362.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][14 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x363);
          reg = x363;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x364 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x364 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x365 = x362 - x364;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x366 = x365 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x367 = Fp(x366.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][15 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x367);
          reg = x367;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x368 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x368 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x369 = x366 - x368;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x370 = x369 * x3;
      // loc("./cirgen/components/bits.h":61:23)
      {
        auto& reg = args[2][74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x370);
        reg = x370;
      }
      if (x349 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x371 = x316 - x320;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x371 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x372 = x317 - x321;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x372 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x373 = x318 - x322;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x373 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x374 = x319 - x323;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x374 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
    auto x375 = args[2][136 * steps + ((cycle - 0) & mask)];
    assert(x375 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
    auto x376 = args[2][137 * steps + ((cycle - 0) & mask)];
    assert(x376 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
    auto x377 = args[2][138 * steps + ((cycle - 0) & mask)];
    assert(x377 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x378 = args[2][146 * steps + ((cycle - 0) & mask)];
    assert(x378 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x379 = args[2][147 * steps + ((cycle - 0) & mask)];
    assert(x379 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x380 = args[2][148 * steps + ((cycle - 0) & mask)];
    assert(x380 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x381 = args[2][149 * steps + ((cycle - 0) & mask)];
    assert(x381 != Fp::invalid());
    {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x382 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x382 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x383 = x375 - x382;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x384 = (x383 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x385 = x7 - x384;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][158 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x385);
        reg = x385;
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x386 = args[2][158 * steps + ((cycle - 0) & mask)];
    assert(x386 != Fp::invalid());
    if (x386 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x387 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x387 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x388 = x6 - x387;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x388 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x389 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x389 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x390 = x389 - x375;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x391 = x390 - x7;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x392 = Fp(x391.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][16 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x392);
          reg = x392;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x393 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x393 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x394 = x391 - x393;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x395 = x394 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x396 = Fp(x395.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][17 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x396);
          reg = x396;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x397 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x397 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x398 = x395 - x397;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x399 = x398 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x400 = Fp(x399.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][18 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x400);
          reg = x400;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x401 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x401 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x402 = x399 - x401;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x403 = x402 * x3;
      // loc("./cirgen/components/bits.h":61:23)
      {
        auto& reg = args[2][75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x403);
        reg = x403;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x404 = x7 - x386;
    if (x404 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x405 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x405 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x406 = x7 - x405;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x407 = x5 - x405;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x408 = x406 * x407;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x408 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x409 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x409 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x410 = x375 - x409;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x410 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x411 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x411 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x412 = x411 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x413 = x412 + x405;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x414 = x376 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x415 = x413 - x414;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x416 = x415 + x377;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x417 = Fp(x416.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][16 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x417);
          reg = x417;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x418 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x418 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x419 = x416 - x418;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x420 = x419 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x421 = Fp(x420.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][17 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x421);
          reg = x421;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x422 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x422 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x423 = x420 - x422;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x424 = x423 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x425 = Fp(x424.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][18 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x425);
          reg = x425;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x426 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x426 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x427 = x424 - x426;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x428 = x427 * x3;
      // loc("./cirgen/components/bits.h":61:23)
      {
        auto& reg = args[2][75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x428);
        reg = x428;
      }
      if (x407 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x429 = x320 - x378;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x429 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x430 = x321 - x379;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x430 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x431 = x322 - x380;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x431 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x432 = x323 - x381;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x432 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
    auto x433 = args[2][143 * steps + ((cycle - 0) & mask)];
    assert(x433 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
    auto x434 = args[2][144 * steps + ((cycle - 0) & mask)];
    assert(x434 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
    auto x435 = args[2][145 * steps + ((cycle - 0) & mask)];
    assert(x435 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x436 = args[2][153 * steps + ((cycle - 0) & mask)];
    assert(x436 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x437 = args[2][154 * steps + ((cycle - 0) & mask)];
    assert(x437 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x438 = args[2][155 * steps + ((cycle - 0) & mask)];
    assert(x438 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x439 = args[2][156 * steps + ((cycle - 0) & mask)];
    assert(x439 != Fp::invalid());
    {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x440 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x440 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x441 = x433 - x440;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x442 = (x441 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x443 = x7 - x442;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][159 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x443);
        reg = x443;
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x444 = args[2][159 * steps + ((cycle - 0) & mask)];
    assert(x444 != Fp::invalid());
    if (x444 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x445 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x445 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x446 = x6 - x445;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x446 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x447 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x447 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x448 = x447 - x433;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x449 = x448 - x7;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x450 = Fp(x449.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][19 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x450);
          reg = x450;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x451 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x451 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x452 = x449 - x451;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x453 = x452 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x454 = Fp(x453.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][20 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x454);
          reg = x454;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x455 = args[2][20 * steps + ((cycle - 0) & mask)];
      assert(x455 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x456 = x453 - x455;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x457 = x456 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x458 = Fp(x457.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x458);
          reg = x458;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x459 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x459 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x460 = x457 - x459;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x461 = x460 * x3;
      // loc("./cirgen/components/bits.h":61:23)
      {
        auto& reg = args[2][76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x461);
        reg = x461;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x462 = x7 - x444;
    if (x462 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x463 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x463 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x464 = x7 - x463;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x465 = x5 - x463;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x466 = x464 * x465;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x466 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x467 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x467 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x468 = x433 - x467;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x468 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x469 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x469 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x470 = x469 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x471 = x470 + x463;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x472 = x434 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x473 = x471 - x472;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x474 = x473 + x435;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x475 = Fp(x474.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][19 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x475);
          reg = x475;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x476 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x476 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x477 = x474 - x476;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x478 = x477 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x479 = Fp(x478.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][20 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x479);
          reg = x479;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x480 = args[2][20 * steps + ((cycle - 0) & mask)];
      assert(x480 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x481 = x478 - x480;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x482 = x481 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x483 = Fp(x482.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x483);
          reg = x483;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x484 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x484 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x485 = x482 - x484;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x486 = x485 * x3;
      // loc("./cirgen/components/bits.h":61:23)
      {
        auto& reg = args[2][76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x486);
        reg = x486;
      }
      if (x465 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x487 = x378 - x436;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x487 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x488 = x379 - x437;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x488 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x489 = x380 - x438;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x489 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x490 = x381 - x439;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x490 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
    auto x491 = args[2][150 * steps + ((cycle - 0) & mask)];
    assert(x491 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
    auto x492 = args[2][151 * steps + ((cycle - 0) & mask)];
    assert(x492 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
    auto x493 = args[2][152 * steps + ((cycle - 0) & mask)];
    assert(x493 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x494 = args[2][5 * steps + ((cycle - 0) & mask)];
    assert(x494 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x495 = args[2][6 * steps + ((cycle - 0) & mask)];
    assert(x495 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x496 = args[2][7 * steps + ((cycle - 0) & mask)];
    assert(x496 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x497 = args[2][8 * steps + ((cycle - 0) & mask)];
    assert(x497 != Fp::invalid());
    {
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x498 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x498 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x499 = x491 - x498;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x500 = (x499 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x501 = x7 - x500;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][160 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x501);
        reg = x501;
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x502 = args[2][160 * steps + ((cycle - 0) & mask)];
    assert(x502 != Fp::invalid());
    if (x502 != 0) {
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x503 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x503 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x504 = x6 - x503;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x504 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x505 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x505 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x506 = x505 - x491;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x507 = x506 - x7;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x508 = Fp(x507.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x508);
          reg = x508;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x509 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x509 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x510 = x507 - x509;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x511 = x510 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x512 = Fp(x511.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x512);
          reg = x512;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x513 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x513 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x514 = x511 - x513;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x515 = x514 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x516 = Fp(x515.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x516);
          reg = x516;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x517 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x517 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x518 = x515 - x517;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x519 = x518 * x3;
      // loc("./cirgen/components/bits.h":61:23)
      {
        auto& reg = args[2][77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x519);
        reg = x519;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x520 = x7 - x502;
    if (x520 != 0) {
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x521 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x521 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x522 = x7 - x521;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x523 = x5 - x521;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x524 = x522 * x523;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x524 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x525 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x525 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x526 = x491 - x525;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x526 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x527 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x527 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x528 = x527 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x529 = x528 + x521;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x530 = x492 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x531 = x529 - x530;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x532 = x531 + x493;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x533 = Fp(x532.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x533);
          reg = x533;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x534 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x534 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x535 = x532 - x534;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x536 = x535 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x537 = Fp(x536.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x537);
          reg = x537;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x538 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x538 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x539 = x536 - x538;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x540 = x539 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x541 = Fp(x540.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x541);
          reg = x541;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x542 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x542 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x543 = x540 - x542;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x544 = x543 * x3;
      // loc("./cirgen/components/bits.h":61:23)
      {
        auto& reg = args[2][77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x544);
        reg = x544;
      }
      if (x523 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x545 = x436 - x494;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x545 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x546 = x437 - x495;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x546 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x547 = x438 - x496;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x547 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x548 = x439 - x497;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x548 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
  }
  if (x11 != 0) {
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x549 = args[2][94 * steps + ((cycle - 0) & mask)];
    assert(x549 != Fp::invalid());
    if (x549 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x550 = host_outs.at(0);
        auto x551 = host_outs.at(1);
        auto x552 = host_outs.at(2);
        auto x553 = host_outs.at(3);
        auto x554 = host_outs.at(4);
        auto x555 = host_outs.at(5);
        auto x556 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x550);
          reg = x550;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x551);
          reg = x551;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x552);
          reg = x552;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x553);
          reg = x553;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x554);
          reg = x554;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][141 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x555);
          reg = x555;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x556);
          reg = x556;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x557 = host_outs.at(0);
        auto x558 = host_outs.at(1);
        auto x559 = host_outs.at(2);
        auto x560 = host_outs.at(3);
        auto x561 = host_outs.at(4);
        auto x562 = host_outs.at(5);
        auto x563 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x557);
          reg = x557;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x558);
          reg = x558;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x559);
          reg = x559;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x560);
          reg = x560;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x561);
          reg = x561;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x562);
          reg = x562;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x563);
          reg = x563;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x564 = host_outs.at(0);
        auto x565 = host_outs.at(1);
        auto x566 = host_outs.at(2);
        auto x567 = host_outs.at(3);
        auto x568 = host_outs.at(4);
        auto x569 = host_outs.at(5);
        auto x570 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x564);
          reg = x564;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x565);
          reg = x565;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x566);
          reg = x566;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x567);
          reg = x567;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x568);
          reg = x568;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x569);
          reg = x569;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x570);
          reg = x570;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x571 = host_outs.at(0);
        auto x572 = host_outs.at(1);
        auto x573 = host_outs.at(2);
        auto x574 = host_outs.at(3);
        auto x575 = host_outs.at(4);
        auto x576 = host_outs.at(5);
        auto x577 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x571);
          reg = x571;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x572);
          reg = x572;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x573);
          reg = x573;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x574);
          reg = x574;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x575);
          reg = x575;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x576);
          reg = x576;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x577);
          reg = x577;
        }
      }
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x578 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x578 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x579 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x579 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x580 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x580 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x581 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x581 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x582 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x582 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x583 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x583 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x584 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x584 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x585 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x585 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x586 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x586 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x587 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x587 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x588 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x588 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x589 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x589 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x590 = x578 - x589;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x591 = (x590 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x592 = x7 - x591;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x592);
          reg = x592;
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x593 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x593 != Fp::invalid());
      if (x593 != 0) {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x594 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x594 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x595 = x6 - x594;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x595 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x596 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x596 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x597 = x596 - x578;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x598 = x597 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x599 = Fp(x598.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x599);
            reg = x599;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x600 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x600 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x601 = x598 - x600;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x602 = x601 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x603 = Fp(x602.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x603);
            reg = x603;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x604 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x604 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x605 = x602 - x604;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x606 = x605 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x607 = Fp(x606.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x607);
            reg = x607;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x608 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x608 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x609 = x606 - x608;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x610 = x609 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x610);
          reg = x610;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x611 = x7 - x593;
      if (x611 != 0) {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x612 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x612 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x613 = x7 - x612;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x614 = x5 - x612;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x615 = x613 * x614;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x615 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x616 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x616 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x617 = x578 - x616;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x617 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x618 = args[2][137 * steps + ((cycle - 0) & mask)];
        assert(x618 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x619 = x618 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x620 = x619 + x612;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x621 = x579 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x622 = x620 - x621;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x623 = x622 + x580;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x624 = Fp(x623.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x624);
            reg = x624;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x625 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x625 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x626 = x623 - x625;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x627 = x626 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x628 = Fp(x627.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x628);
            reg = x628;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x629 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x629 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x630 = x627 - x629;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x631 = x630 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x632 = Fp(x631.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x632);
            reg = x632;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x633 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x633 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x634 = x631 - x633;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x635 = x634 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x635);
          reg = x635;
        }
        if (x614 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x636 = x581 - x585;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x636 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x637 = x582 - x586;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x637 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x638 = x583 - x587;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x638 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x639 = x584 - x588;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x639 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x640 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x640 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x641 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x641 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x642 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x642 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x643 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x643 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x644 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x644 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x645 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x645 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x646 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x646 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x647 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x647 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x648 = x640 - x647;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x649 = (x648 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x650 = x7 - x649;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x650);
          reg = x650;
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x651 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x651 != Fp::invalid());
      if (x651 != 0) {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x652 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x652 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x653 = x6 - x652;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x653 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x654 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x654 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x655 = x654 - x640;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x656 = x655 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x657 = Fp(x656.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x657);
            reg = x657;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x658 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x658 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x659 = x656 - x658;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x660 = x659 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x661 = Fp(x660.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x661);
            reg = x661;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x662 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x662 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x663 = x660 - x662;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x664 = x663 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x665 = Fp(x664.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x665);
            reg = x665;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x666 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x666 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x667 = x664 - x666;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x668 = x667 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x668);
          reg = x668;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x669 = x7 - x651;
      if (x669 != 0) {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x670 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x670 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x671 = x7 - x670;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x672 = x5 - x670;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x673 = x671 * x672;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x673 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x674 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x674 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x675 = x640 - x674;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x675 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x676 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x676 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x677 = x676 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x678 = x677 + x670;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x679 = x641 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x680 = x678 - x679;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x681 = x680 + x642;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x682 = Fp(x681.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x682);
            reg = x682;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x683 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x683 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x684 = x681 - x683;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x685 = x684 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x686 = Fp(x685.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x686);
            reg = x686;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x687 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x687 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x688 = x685 - x687;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x689 = x688 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x690 = Fp(x689.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x690);
            reg = x690;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x691 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x691 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x692 = x689 - x691;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x693 = x692 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x693);
          reg = x693;
        }
        if (x672 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x694 = x585 - x643;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x694 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x695 = x586 - x644;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x695 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x696 = x587 - x645;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x696 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x697 = x588 - x646;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x697 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x698 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x698 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x699 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x699 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x700 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x700 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x701 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x701 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x702 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x702 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x703 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x703 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x704 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x704 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x705 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x705 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x706 = x698 - x705;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x707 = (x706 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x708 = x7 - x707;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x708);
          reg = x708;
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x709 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x709 != Fp::invalid());
      if (x709 != 0) {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x710 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x710 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x711 = x6 - x710;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x711 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x712 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x712 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x713 = x712 - x698;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x714 = x713 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x715 = Fp(x714.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x715);
            reg = x715;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x716 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x716 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x717 = x714 - x716;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x718 = x717 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x719 = Fp(x718.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x719);
            reg = x719;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x720 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x720 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x721 = x718 - x720;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x722 = x721 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x723 = Fp(x722.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x723);
            reg = x723;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x724 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x724 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x725 = x722 - x724;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x726 = x725 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x726);
          reg = x726;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x727 = x7 - x709;
      if (x727 != 0) {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x728 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x728 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x729 = x7 - x728;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x730 = x5 - x728;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x731 = x729 * x730;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x731 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x732 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x732 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x733 = x698 - x732;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x733 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x734 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x734 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x735 = x734 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x736 = x735 + x728;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x737 = x699 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x738 = x736 - x737;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x739 = x738 + x700;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x740 = Fp(x739.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x740);
            reg = x740;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x741 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x741 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x742 = x739 - x741;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x743 = x742 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x744 = Fp(x743.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x744);
            reg = x744;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x745 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x745 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x746 = x743 - x745;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x747 = x746 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x748 = Fp(x747.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x748);
            reg = x748;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x749 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x749 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x750 = x747 - x749;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x751 = x750 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x751);
          reg = x751;
        }
        if (x730 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x752 = x643 - x701;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x752 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x753 = x644 - x702;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x753 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x754 = x645 - x703;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x754 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x755 = x646 - x704;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x755 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x756 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x756 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x757 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x757 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x758 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x758 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x759 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x759 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x760 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x760 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x761 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x761 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x762 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x762 != Fp::invalid());
      {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x763 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x763 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x764 = x756 - x763;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x765 = (x764 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x766 = x7 - x765;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x766);
          reg = x766;
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x767 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x767 != Fp::invalid());
      if (x767 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x768 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x768 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x769 = x6 - x768;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x769 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x770 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x770 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x771 = x770 - x756;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x772 = x771 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x773 = Fp(x772.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x773);
            reg = x773;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x774 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x774 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x775 = x772 - x774;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x776 = x775 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x777 = Fp(x776.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x777);
            reg = x777;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x778 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x778 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x779 = x776 - x778;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x780 = x779 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x781 = Fp(x780.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x781);
            reg = x781;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x782 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x782 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x783 = x780 - x782;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x784 = x783 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x784);
          reg = x784;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x785 = x7 - x767;
      if (x785 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x786 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x786 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x787 = x7 - x786;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x788 = x5 - x786;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x789 = x787 * x788;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x789 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x790 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x790 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x791 = x756 - x790;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x791 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x792 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x792 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x793 = x792 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x794 = x793 + x786;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x795 = x757 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x796 = x794 - x795;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x797 = x796 + x758;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x798 = Fp(x797.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x798);
            reg = x798;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x799 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x799 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x800 = x797 - x799;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x801 = x800 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x802 = Fp(x801.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x802);
            reg = x802;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x803 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x803 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x804 = x801 - x803;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x805 = x804 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x806 = Fp(x805.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x806);
            reg = x806;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x807 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x807 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x808 = x805 - x807;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x809 = x808 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x809);
          reg = x809;
        }
        if (x788 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x810 = x701 - x759;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x810 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x811 = x702 - x760;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x811 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x812 = x703 - x761;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x812 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x813 = x704 - x762;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x813 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x814 = args[2][95 * steps + ((cycle - 0) & mask)];
    assert(x814 != Fp::invalid());
    if (x814 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x815 = host_outs.at(0);
        auto x816 = host_outs.at(1);
        auto x817 = host_outs.at(2);
        auto x818 = host_outs.at(3);
        auto x819 = host_outs.at(4);
        auto x820 = host_outs.at(5);
        auto x821 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x815);
          reg = x815;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x816);
          reg = x816;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x817);
          reg = x817;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x818);
          reg = x818;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x819);
          reg = x819;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][141 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x820);
          reg = x820;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x821);
          reg = x821;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x822 = host_outs.at(0);
        auto x823 = host_outs.at(1);
        auto x824 = host_outs.at(2);
        auto x825 = host_outs.at(3);
        auto x826 = host_outs.at(4);
        auto x827 = host_outs.at(5);
        auto x828 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x822);
          reg = x822;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x823);
          reg = x823;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x824);
          reg = x824;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x825);
          reg = x825;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x826);
          reg = x826;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x827);
          reg = x827;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x828);
          reg = x828;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x829 = host_outs.at(0);
        auto x830 = host_outs.at(1);
        auto x831 = host_outs.at(2);
        auto x832 = host_outs.at(3);
        auto x833 = host_outs.at(4);
        auto x834 = host_outs.at(5);
        auto x835 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x829);
          reg = x829;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x830);
          reg = x830;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x831);
          reg = x831;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x832);
          reg = x832;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x833);
          reg = x833;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x834);
          reg = x834;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x835);
          reg = x835;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x836 = host_outs.at(0);
        auto x837 = host_outs.at(1);
        auto x838 = host_outs.at(2);
        auto x839 = host_outs.at(3);
        auto x840 = host_outs.at(4);
        auto x841 = host_outs.at(5);
        auto x842 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x836);
          reg = x836;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x837);
          reg = x837;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x838);
          reg = x838;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x839);
          reg = x839;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x840);
          reg = x840;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x841);
          reg = x841;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x842);
          reg = x842;
        }
      }
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x843 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x843 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x844 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x844 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x845 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x845 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x846 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x846 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x847 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x847 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x848 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x848 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x849 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x849 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x850 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x850 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x851 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x851 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x852 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x852 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x853 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x853 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x854 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x854 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x855 = x843 - x854;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x856 = (x855 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x857 = x7 - x856;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x857);
          reg = x857;
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x858 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x858 != Fp::invalid());
      if (x858 != 0) {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x859 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x859 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x860 = x6 - x859;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x860 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x861 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x861 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x862 = x861 - x843;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x863 = x862 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x864 = Fp(x863.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x864);
            reg = x864;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x865 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x865 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x866 = x863 - x865;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x867 = x866 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x868 = Fp(x867.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x868);
            reg = x868;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x869 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x869 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x870 = x867 - x869;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x871 = x870 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x872 = Fp(x871.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x872);
            reg = x872;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x873 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x873 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x874 = x871 - x873;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x875 = x874 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x875);
          reg = x875;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x876 = x7 - x858;
      if (x876 != 0) {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x877 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x877 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x878 = x7 - x877;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x879 = x5 - x877;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x880 = x878 * x879;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x880 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x881 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x881 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x882 = x843 - x881;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x882 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x883 = args[2][137 * steps + ((cycle - 0) & mask)];
        assert(x883 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x884 = x883 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x885 = x884 + x877;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x886 = x844 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x887 = x885 - x886;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x888 = x887 + x845;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x889 = Fp(x888.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x889);
            reg = x889;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x890 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x890 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x891 = x888 - x890;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x892 = x891 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x893 = Fp(x892.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x893);
            reg = x893;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x894 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x894 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x895 = x892 - x894;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x896 = x895 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x897 = Fp(x896.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x897);
            reg = x897;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x898 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x898 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x899 = x896 - x898;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x900 = x899 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x900);
          reg = x900;
        }
        if (x879 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x901 = x846 - x850;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x901 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x902 = x847 - x851;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x902 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x903 = x848 - x852;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x903 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x904 = x849 - x853;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x904 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x905 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x905 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x906 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x906 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x907 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x907 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x908 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x908 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x909 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x909 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x910 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x910 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x911 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x911 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x912 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x912 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x913 = x905 - x912;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x914 = (x913 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x915 = x7 - x914;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x915);
          reg = x915;
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x916 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x916 != Fp::invalid());
      if (x916 != 0) {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x917 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x917 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x918 = x6 - x917;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x918 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x919 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x919 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x920 = x919 - x905;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x921 = x920 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x922 = Fp(x921.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x922);
            reg = x922;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x923 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x923 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x924 = x921 - x923;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x925 = x924 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x926 = Fp(x925.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x926);
            reg = x926;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x927 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x927 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x928 = x925 - x927;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x929 = x928 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x930 = Fp(x929.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x930);
            reg = x930;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x931 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x931 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x932 = x929 - x931;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x933 = x932 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x933);
          reg = x933;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x934 = x7 - x916;
      if (x934 != 0) {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x935 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x935 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x936 = x7 - x935;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x937 = x5 - x935;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x938 = x936 * x937;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x938 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x939 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x939 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x940 = x905 - x939;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x940 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x941 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x941 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x942 = x941 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x943 = x942 + x935;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x944 = x906 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x945 = x943 - x944;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x946 = x945 + x907;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x947 = Fp(x946.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x947);
            reg = x947;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x948 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x948 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x949 = x946 - x948;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x950 = x949 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x951 = Fp(x950.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x951);
            reg = x951;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x952 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x952 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x953 = x950 - x952;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x954 = x953 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x955 = Fp(x954.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x955);
            reg = x955;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x956 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x956 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x957 = x954 - x956;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x958 = x957 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x958);
          reg = x958;
        }
        if (x937 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x959 = x850 - x908;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x959 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x960 = x851 - x909;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x960 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x961 = x852 - x910;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x961 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x962 = x853 - x911;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x962 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x963 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x963 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x964 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x964 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x965 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x965 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x966 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x966 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x967 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x967 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x968 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x968 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x969 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x969 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x970 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x970 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x971 = x963 - x970;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x972 = (x971 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x973 = x7 - x972;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x973);
          reg = x973;
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x974 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x974 != Fp::invalid());
      if (x974 != 0) {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x975 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x975 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x976 = x6 - x975;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x976 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x977 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x977 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x978 = x977 - x963;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x979 = x978 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x980 = Fp(x979.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x980);
            reg = x980;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x981 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x981 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x982 = x979 - x981;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x983 = x982 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x984 = Fp(x983.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x984);
            reg = x984;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x985 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x985 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x986 = x983 - x985;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x987 = x986 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x988 = Fp(x987.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x988);
            reg = x988;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x989 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x989 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x990 = x987 - x989;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x991 = x990 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x991);
          reg = x991;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x992 = x7 - x974;
      if (x992 != 0) {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x993 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x993 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x994 = x7 - x993;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x995 = x5 - x993;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x996 = x994 * x995;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x996 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x997 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x997 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x998 = x963 - x997;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x998 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x999 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x999 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1000 = x999 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1001 = x1000 + x993;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1002 = x964 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1003 = x1001 - x1002;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1004 = x1003 + x965;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1005 = Fp(x1004.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1005);
            reg = x1005;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1006 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x1006 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1007 = x1004 - x1006;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1008 = x1007 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1009 = Fp(x1008.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1009);
            reg = x1009;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1010 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x1010 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1011 = x1008 - x1010;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1012 = x1011 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1013 = Fp(x1012.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1013);
            reg = x1013;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1014 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x1014 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1015 = x1012 - x1014;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1016 = x1015 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1016);
          reg = x1016;
        }
        if (x995 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1017 = x908 - x966;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1017 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1018 = x909 - x967;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1018 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1019 = x910 - x968;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1019 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1020 = x911 - x969;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1020 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1021 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x1021 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x1022 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x1022 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x1023 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x1023 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1024 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x1024 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1025 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x1025 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1026 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x1026 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1027 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x1027 != Fp::invalid());
      {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1028 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1028 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1029 = x1021 - x1028;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1030 = (x1029 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1031 = x7 - x1030;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1031);
          reg = x1031;
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1032 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x1032 != Fp::invalid());
      if (x1032 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1033 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x1033 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1034 = x6 - x1033;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1034 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1035 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1035 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1036 = x1035 - x1021;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1037 = x1036 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1038 = Fp(x1037.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1038);
            reg = x1038;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1039 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1039 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1040 = x1037 - x1039;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1041 = x1040 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1042 = Fp(x1041.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1042);
            reg = x1042;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1043 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1043 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1044 = x1041 - x1043;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1045 = x1044 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1046 = Fp(x1045.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1046);
            reg = x1046;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1047 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1047 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1048 = x1045 - x1047;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1049 = x1048 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1049);
          reg = x1049;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1050 = x7 - x1032;
      if (x1050 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1051 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x1051 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1052 = x7 - x1051;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1053 = x5 - x1051;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1054 = x1052 * x1053;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1054 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1055 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1055 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1056 = x1021 - x1055;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1056 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1057 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x1057 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1058 = x1057 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1059 = x1058 + x1051;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1060 = x1022 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1061 = x1059 - x1060;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1062 = x1061 + x1023;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1063 = Fp(x1062.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1063);
            reg = x1063;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1064 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1064 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1065 = x1062 - x1064;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1066 = x1065 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1067 = Fp(x1066.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1067);
            reg = x1067;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1068 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1068 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1069 = x1066 - x1068;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1070 = x1069 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1071 = Fp(x1070.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1071);
            reg = x1071;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1072 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1072 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1073 = x1070 - x1072;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1074 = x1073 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1074);
          reg = x1074;
        }
        if (x1053 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1075 = x966 - x1024;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1075 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1076 = x967 - x1025;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1076 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1077 = x968 - x1026;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1077 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1078 = x969 - x1027;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1078 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x1079 = args[2][96 * steps + ((cycle - 0) & mask)];
    assert(x1079 != Fp::invalid());
    if (x1079 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1080 = host_outs.at(0);
        auto x1081 = host_outs.at(1);
        auto x1082 = host_outs.at(2);
        auto x1083 = host_outs.at(3);
        auto x1084 = host_outs.at(4);
        auto x1085 = host_outs.at(5);
        auto x1086 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1080);
          reg = x1080;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1081);
          reg = x1081;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1082);
          reg = x1082;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1083);
          reg = x1083;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1084);
          reg = x1084;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][141 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1085);
          reg = x1085;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1086);
          reg = x1086;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1087 = host_outs.at(0);
        auto x1088 = host_outs.at(1);
        auto x1089 = host_outs.at(2);
        auto x1090 = host_outs.at(3);
        auto x1091 = host_outs.at(4);
        auto x1092 = host_outs.at(5);
        auto x1093 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1087);
          reg = x1087;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1088);
          reg = x1088;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1089);
          reg = x1089;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1090);
          reg = x1090;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1091);
          reg = x1091;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1092);
          reg = x1092;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1093);
          reg = x1093;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1094 = host_outs.at(0);
        auto x1095 = host_outs.at(1);
        auto x1096 = host_outs.at(2);
        auto x1097 = host_outs.at(3);
        auto x1098 = host_outs.at(4);
        auto x1099 = host_outs.at(5);
        auto x1100 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1094);
          reg = x1094;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1095);
          reg = x1095;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1096);
          reg = x1096;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1097);
          reg = x1097;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1098);
          reg = x1098;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1099);
          reg = x1099;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1100);
          reg = x1100;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1101 = host_outs.at(0);
        auto x1102 = host_outs.at(1);
        auto x1103 = host_outs.at(2);
        auto x1104 = host_outs.at(3);
        auto x1105 = host_outs.at(4);
        auto x1106 = host_outs.at(5);
        auto x1107 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1101);
          reg = x1101;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1102);
          reg = x1102;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1103);
          reg = x1103;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1104);
          reg = x1104;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1105);
          reg = x1105;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1106);
          reg = x1106;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1107);
          reg = x1107;
        }
      }
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1108 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x1108 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x1109 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x1109 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x1110 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x1110 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1111 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x1111 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1112 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x1112 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1113 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x1113 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1114 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x1114 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1115 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x1115 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1116 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x1116 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1117 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x1117 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1118 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x1118 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1119 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x1119 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1120 = x1108 - x1119;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1121 = (x1120 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1122 = x7 - x1121;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1122);
          reg = x1122;
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1123 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x1123 != Fp::invalid());
      if (x1123 != 0) {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1124 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x1124 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1125 = x6 - x1124;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1125 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1126 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x1126 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1127 = x1126 - x1108;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1128 = x1127 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1129 = Fp(x1128.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1129);
            reg = x1129;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1130 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1130 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1131 = x1128 - x1130;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1132 = x1131 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1133 = Fp(x1132.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1133);
            reg = x1133;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1134 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1134 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1135 = x1132 - x1134;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1136 = x1135 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1137 = Fp(x1136.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1137);
            reg = x1137;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1138 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1138 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1139 = x1136 - x1138;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1140 = x1139 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1140);
          reg = x1140;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1141 = x7 - x1123;
      if (x1141 != 0) {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1142 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x1142 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1143 = x7 - x1142;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1144 = x5 - x1142;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1145 = x1143 * x1144;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1145 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1146 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x1146 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1147 = x1108 - x1146;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1147 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1148 = args[2][137 * steps + ((cycle - 0) & mask)];
        assert(x1148 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1149 = x1148 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1150 = x1149 + x1142;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1151 = x1109 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1152 = x1150 - x1151;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1153 = x1152 + x1110;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1154 = Fp(x1153.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1154);
            reg = x1154;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1155 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1155 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1156 = x1153 - x1155;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1157 = x1156 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1158 = Fp(x1157.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1158);
            reg = x1158;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1159 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1159 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1160 = x1157 - x1159;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1161 = x1160 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1162 = Fp(x1161.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1162);
            reg = x1162;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1163 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1163 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1164 = x1161 - x1163;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1165 = x1164 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1165);
          reg = x1165;
        }
        if (x1144 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1166 = x1111 - x1115;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1166 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1167 = x1112 - x1116;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1167 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1168 = x1113 - x1117;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1168 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1169 = x1114 - x1118;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1169 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1170 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x1170 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x1171 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x1171 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x1172 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x1172 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1173 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x1173 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1174 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x1174 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1175 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x1175 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1176 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x1176 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1177 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1177 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1178 = x1170 - x1177;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1179 = (x1178 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1180 = x7 - x1179;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1180);
          reg = x1180;
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1181 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x1181 != Fp::invalid());
      if (x1181 != 0) {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1182 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x1182 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1183 = x6 - x1182;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1183 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1184 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1184 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1185 = x1184 - x1170;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1186 = x1185 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1187 = Fp(x1186.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1187);
            reg = x1187;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1188 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x1188 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1189 = x1186 - x1188;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1190 = x1189 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1191 = Fp(x1190.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1191);
            reg = x1191;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1192 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x1192 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1193 = x1190 - x1192;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1194 = x1193 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1195 = Fp(x1194.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1195);
            reg = x1195;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1196 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x1196 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1197 = x1194 - x1196;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1198 = x1197 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1198);
          reg = x1198;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1199 = x7 - x1181;
      if (x1199 != 0) {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1200 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x1200 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1201 = x7 - x1200;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1202 = x5 - x1200;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1203 = x1201 * x1202;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1203 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1204 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1204 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1205 = x1170 - x1204;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1205 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1206 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x1206 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1207 = x1206 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1208 = x1207 + x1200;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1209 = x1171 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1210 = x1208 - x1209;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1211 = x1210 + x1172;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1212 = Fp(x1211.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1212);
            reg = x1212;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1213 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x1213 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1214 = x1211 - x1213;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1215 = x1214 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1216 = Fp(x1215.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1216);
            reg = x1216;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1217 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x1217 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1218 = x1215 - x1217;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1219 = x1218 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1220 = Fp(x1219.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1220);
            reg = x1220;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1221 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x1221 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1222 = x1219 - x1221;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1223 = x1222 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1223);
          reg = x1223;
        }
        if (x1202 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1224 = x1115 - x1173;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1224 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1225 = x1116 - x1174;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1225 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1226 = x1117 - x1175;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1226 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1227 = x1118 - x1176;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1227 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1228 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x1228 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x1229 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x1229 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x1230 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x1230 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1231 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x1231 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1232 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x1232 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1233 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x1233 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1234 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x1234 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1235 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1235 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1236 = x1228 - x1235;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1237 = (x1236 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1238 = x7 - x1237;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1238);
          reg = x1238;
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1239 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x1239 != Fp::invalid());
      if (x1239 != 0) {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1240 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x1240 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1241 = x6 - x1240;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1241 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1242 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1242 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1243 = x1242 - x1228;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1244 = x1243 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1245 = Fp(x1244.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1245);
            reg = x1245;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1246 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x1246 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1247 = x1244 - x1246;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1248 = x1247 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1249 = Fp(x1248.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1249);
            reg = x1249;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1250 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x1250 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1251 = x1248 - x1250;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1252 = x1251 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1253 = Fp(x1252.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1253);
            reg = x1253;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1254 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x1254 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1255 = x1252 - x1254;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1256 = x1255 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1256);
          reg = x1256;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1257 = x7 - x1239;
      if (x1257 != 0) {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1258 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x1258 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1259 = x7 - x1258;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1260 = x5 - x1258;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1261 = x1259 * x1260;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1261 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1262 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1262 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1263 = x1228 - x1262;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1263 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1264 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x1264 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1265 = x1264 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1266 = x1265 + x1258;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1267 = x1229 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1268 = x1266 - x1267;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1269 = x1268 + x1230;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1270 = Fp(x1269.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1270);
            reg = x1270;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1271 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x1271 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1272 = x1269 - x1271;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1273 = x1272 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1274 = Fp(x1273.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1274);
            reg = x1274;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1275 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x1275 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1276 = x1273 - x1275;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1277 = x1276 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1278 = Fp(x1277.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1278);
            reg = x1278;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1279 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x1279 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1280 = x1277 - x1279;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1281 = x1280 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1281);
          reg = x1281;
        }
        if (x1260 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1282 = x1173 - x1231;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1282 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1283 = x1174 - x1232;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1283 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1284 = x1175 - x1233;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1284 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1285 = x1176 - x1234;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1285 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1286 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x1286 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x1287 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x1287 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x1288 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x1288 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1289 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x1289 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1290 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x1290 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1291 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x1291 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1292 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x1292 != Fp::invalid());
      {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1293 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1293 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1294 = x1286 - x1293;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1295 = (x1294 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1296 = x7 - x1295;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1296);
          reg = x1296;
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1297 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x1297 != Fp::invalid());
      if (x1297 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1298 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x1298 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1299 = x6 - x1298;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1299 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1300 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1300 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1301 = x1300 - x1286;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1302 = x1301 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1303 = Fp(x1302.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1303);
            reg = x1303;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1304 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1304 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1305 = x1302 - x1304;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1306 = x1305 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1307 = Fp(x1306.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1307);
            reg = x1307;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1308 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1308 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1309 = x1306 - x1308;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1310 = x1309 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1311 = Fp(x1310.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1311);
            reg = x1311;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1312 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1312 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1313 = x1310 - x1312;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1314 = x1313 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1314);
          reg = x1314;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1315 = x7 - x1297;
      if (x1315 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1316 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x1316 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1317 = x7 - x1316;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1318 = x5 - x1316;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1319 = x1317 * x1318;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1319 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1320 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1320 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1321 = x1286 - x1320;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1321 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1322 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x1322 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1323 = x1322 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1324 = x1323 + x1316;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1325 = x1287 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1326 = x1324 - x1325;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1327 = x1326 + x1288;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1328 = Fp(x1327.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1328);
            reg = x1328;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1329 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1329 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1330 = x1327 - x1329;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1331 = x1330 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1332 = Fp(x1331.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1332);
            reg = x1332;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1333 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1333 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1334 = x1331 - x1333;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1335 = x1334 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1336 = Fp(x1335.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1336);
            reg = x1336;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1337 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1337 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1338 = x1335 - x1337;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1339 = x1338 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1339);
          reg = x1339;
        }
        if (x1318 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1340 = x1231 - x1289;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1340 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1341 = x1232 - x1290;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1341 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1342 = x1233 - x1291;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1342 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1343 = x1234 - x1292;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1343 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x1344 = args[2][97 * steps + ((cycle - 0) & mask)];
    assert(x1344 != Fp::invalid());
    if (x1344 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1345 = host_outs.at(0);
        auto x1346 = host_outs.at(1);
        auto x1347 = host_outs.at(2);
        auto x1348 = host_outs.at(3);
        auto x1349 = host_outs.at(4);
        auto x1350 = host_outs.at(5);
        auto x1351 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1345);
          reg = x1345;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1346);
          reg = x1346;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1347);
          reg = x1347;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1348);
          reg = x1348;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1349);
          reg = x1349;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1350);
          reg = x1350;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1351);
          reg = x1351;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1352 = host_outs.at(0);
        auto x1353 = host_outs.at(1);
        auto x1354 = host_outs.at(2);
        auto x1355 = host_outs.at(3);
        auto x1356 = host_outs.at(4);
        auto x1357 = host_outs.at(5);
        auto x1358 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1352);
          reg = x1352;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1353);
          reg = x1353;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1354);
          reg = x1354;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1355);
          reg = x1355;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1356);
          reg = x1356;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1357);
          reg = x1357;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1358);
          reg = x1358;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1359 = host_outs.at(0);
        auto x1360 = host_outs.at(1);
        auto x1361 = host_outs.at(2);
        auto x1362 = host_outs.at(3);
        auto x1363 = host_outs.at(4);
        auto x1364 = host_outs.at(5);
        auto x1365 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1359);
          reg = x1359;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1360);
          reg = x1360;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1361);
          reg = x1361;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1362);
          reg = x1362;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][161 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1363);
          reg = x1363;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][162 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1364);
          reg = x1364;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][163 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1365);
          reg = x1365;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1366 = host_outs.at(0);
        auto x1367 = host_outs.at(1);
        auto x1368 = host_outs.at(2);
        auto x1369 = host_outs.at(3);
        auto x1370 = host_outs.at(4);
        auto x1371 = host_outs.at(5);
        auto x1372 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][164 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1366);
          reg = x1366;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][165 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1367);
          reg = x1367;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][166 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1368);
          reg = x1368;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][167 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1369);
          reg = x1369;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1370);
          reg = x1370;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][169 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1371);
          reg = x1371;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1372);
          reg = x1372;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1373 = host_outs.at(0);
        auto x1374 = host_outs.at(1);
        auto x1375 = host_outs.at(2);
        auto x1376 = host_outs.at(3);
        auto x1377 = host_outs.at(4);
        auto x1378 = host_outs.at(5);
        auto x1379 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1373);
          reg = x1373;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1374);
          reg = x1374;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1375);
          reg = x1375;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1376);
          reg = x1376;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1377);
          reg = x1377;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1378);
          reg = x1378;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1379);
          reg = x1379;
        }
      }
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1380 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x1380 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x1381 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x1381 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x1382 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x1382 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1383 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x1383 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1384 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x1384 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1385 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x1385 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1386 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x1386 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1387 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x1387 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1388 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x1388 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1389 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x1389 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1390 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x1390 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1391 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1391 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1392 = x1380 - x1391;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1393 = (x1392 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1394 = x7 - x1393;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][171 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1394);
          reg = x1394;
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1395 = args[2][171 * steps + ((cycle - 0) & mask)];
      assert(x1395 != Fp::invalid());
      if (x1395 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1396 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x1396 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1397 = x6 - x1396;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1397 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1398 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1398 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1399 = x1398 - x1380;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1400 = x1399 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1401 = Fp(x1400.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1401);
            reg = x1401;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1402 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1402 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1403 = x1400 - x1402;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1404 = x1403 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1405 = Fp(x1404.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1405);
            reg = x1405;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1406 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1406 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1407 = x1404 - x1406;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1408 = x1407 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1409 = Fp(x1408.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1409);
            reg = x1409;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1410 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1410 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1411 = x1408 - x1410;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1412 = x1411 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1412);
          reg = x1412;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1413 = x7 - x1395;
      if (x1413 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1414 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x1414 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1415 = x7 - x1414;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1416 = x5 - x1414;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1417 = x1415 * x1416;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1417 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1418 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1418 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1419 = x1380 - x1418;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1419 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1420 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x1420 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1421 = x1420 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1422 = x1421 + x1414;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1423 = x1381 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1424 = x1422 - x1423;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1425 = x1424 + x1382;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1426 = Fp(x1425.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1426);
            reg = x1426;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1427 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1427 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1428 = x1425 - x1427;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1429 = x1428 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1430 = Fp(x1429.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1430);
            reg = x1430;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1431 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1431 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1432 = x1429 - x1431;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1433 = x1432 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1434 = Fp(x1433.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1434);
            reg = x1434;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1435 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1435 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1436 = x1433 - x1435;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1437 = x1436 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1437);
          reg = x1437;
        }
        if (x1416 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1438 = x1383 - x1387;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1438 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1439 = x1384 - x1388;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1439 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1440 = x1385 - x1389;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1440 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1441 = x1386 - x1390;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1441 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1442 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x1442 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x1443 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x1443 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x1444 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x1444 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1445 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x1445 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1446 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x1446 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1447 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x1447 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1448 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x1448 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1449 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1449 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1450 = x1442 - x1449;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1451 = (x1450 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1452 = x7 - x1451;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1452);
          reg = x1452;
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1453 = args[2][172 * steps + ((cycle - 0) & mask)];
      assert(x1453 != Fp::invalid());
      if (x1453 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1454 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x1454 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1455 = x6 - x1454;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1455 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1456 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1456 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1457 = x1456 - x1442;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1458 = x1457 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1459 = Fp(x1458.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1459);
            reg = x1459;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1460 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x1460 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1461 = x1458 - x1460;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1462 = x1461 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1463 = Fp(x1462.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1463);
            reg = x1463;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1464 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x1464 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1465 = x1462 - x1464;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1466 = x1465 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1467 = Fp(x1466.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1467);
            reg = x1467;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1468 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x1468 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1469 = x1466 - x1468;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1470 = x1469 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1470);
          reg = x1470;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1471 = x7 - x1453;
      if (x1471 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1472 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x1472 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1473 = x7 - x1472;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1474 = x5 - x1472;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1475 = x1473 * x1474;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1475 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1476 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1476 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1477 = x1442 - x1476;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1477 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1478 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x1478 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1479 = x1478 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1480 = x1479 + x1472;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1481 = x1443 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1482 = x1480 - x1481;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1483 = x1482 + x1444;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1484 = Fp(x1483.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1484);
            reg = x1484;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1485 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x1485 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1486 = x1483 - x1485;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1487 = x1486 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1488 = Fp(x1487.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1488);
            reg = x1488;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1489 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x1489 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1490 = x1487 - x1489;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1491 = x1490 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1492 = Fp(x1491.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1492);
            reg = x1492;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1493 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x1493 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1494 = x1491 - x1493;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1495 = x1494 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1495);
          reg = x1495;
        }
        if (x1474 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1496 = x1387 - x1445;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1496 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1497 = x1388 - x1446;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1497 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1498 = x1389 - x1447;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1498 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1499 = x1390 - x1448;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1499 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1500 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x1500 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x1501 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x1501 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x1502 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x1502 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1503 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x1503 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1504 = args[2][161 * steps + ((cycle - 0) & mask)];
      assert(x1504 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1505 = args[2][162 * steps + ((cycle - 0) & mask)];
      assert(x1505 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1506 = args[2][163 * steps + ((cycle - 0) & mask)];
      assert(x1506 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1507 = args[2][157 * steps + ((cycle - 0) & mask)];
        assert(x1507 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1508 = x1500 - x1507;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1509 = (x1508 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1510 = x7 - x1509;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][173 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1510);
          reg = x1510;
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1511 = args[2][173 * steps + ((cycle - 0) & mask)];
      assert(x1511 != Fp::invalid());
      if (x1511 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1512 = args[2][159 * steps + ((cycle - 0) & mask)];
        assert(x1512 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1513 = x6 - x1512;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1513 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1514 = args[2][157 * steps + ((cycle - 0) & mask)];
        assert(x1514 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1515 = x1514 - x1500;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1516 = x1515 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1517 = Fp(x1516.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1517);
            reg = x1517;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1518 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x1518 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1519 = x1516 - x1518;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1520 = x1519 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1521 = Fp(x1520.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1521);
            reg = x1521;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1522 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x1522 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1523 = x1520 - x1522;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1524 = x1523 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1525 = Fp(x1524.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1525);
            reg = x1525;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1526 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x1526 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1527 = x1524 - x1526;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1528 = x1527 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1528);
          reg = x1528;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1529 = x7 - x1511;
      if (x1529 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1530 = args[2][159 * steps + ((cycle - 0) & mask)];
        assert(x1530 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1531 = x7 - x1530;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1532 = x5 - x1530;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1533 = x1531 * x1532;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1533 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1534 = args[2][157 * steps + ((cycle - 0) & mask)];
        assert(x1534 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1535 = x1500 - x1534;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1535 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1536 = args[2][158 * steps + ((cycle - 0) & mask)];
        assert(x1536 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1537 = x1536 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1538 = x1537 + x1530;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1539 = x1501 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1540 = x1538 - x1539;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1541 = x1540 + x1502;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1542 = Fp(x1541.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1542);
            reg = x1542;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1543 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x1543 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1544 = x1541 - x1543;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1545 = x1544 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1546 = Fp(x1545.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1546);
            reg = x1546;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1547 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x1547 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1548 = x1545 - x1547;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1549 = x1548 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1550 = Fp(x1549.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1550);
            reg = x1550;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1551 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x1551 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1552 = x1549 - x1551;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1553 = x1552 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1553);
          reg = x1553;
        }
        if (x1532 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1554 = x1445 - x1503;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1554 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1555 = x1446 - x1504;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1555 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1556 = x1447 - x1505;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1556 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1557 = x1448 - x1506;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1557 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1558 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x1558 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x1559 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x1559 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x1560 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x1560 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1561 = args[2][167 * steps + ((cycle - 0) & mask)];
      assert(x1561 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1562 = args[2][168 * steps + ((cycle - 0) & mask)];
      assert(x1562 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1563 = args[2][169 * steps + ((cycle - 0) & mask)];
      assert(x1563 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1564 = args[2][170 * steps + ((cycle - 0) & mask)];
      assert(x1564 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1565 = args[2][164 * steps + ((cycle - 0) & mask)];
        assert(x1565 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1566 = x1558 - x1565;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1567 = (x1566 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1568 = x7 - x1567;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][174 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1568);
          reg = x1568;
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1569 = args[2][174 * steps + ((cycle - 0) & mask)];
      assert(x1569 != Fp::invalid());
      if (x1569 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1570 = args[2][166 * steps + ((cycle - 0) & mask)];
        assert(x1570 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1571 = x6 - x1570;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1571 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1572 = args[2][164 * steps + ((cycle - 0) & mask)];
        assert(x1572 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1573 = x1572 - x1558;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1574 = x1573 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1575 = Fp(x1574.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1575);
            reg = x1575;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1576 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1576 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1577 = x1574 - x1576;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1578 = x1577 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1579 = Fp(x1578.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1579);
            reg = x1579;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1580 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1580 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1581 = x1578 - x1580;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1582 = x1581 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1583 = Fp(x1582.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1583);
            reg = x1583;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1584 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1584 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1585 = x1582 - x1584;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1586 = x1585 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1586);
          reg = x1586;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1587 = x7 - x1569;
      if (x1587 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1588 = args[2][166 * steps + ((cycle - 0) & mask)];
        assert(x1588 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1589 = x7 - x1588;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1590 = x5 - x1588;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1591 = x1589 * x1590;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1591 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1592 = args[2][164 * steps + ((cycle - 0) & mask)];
        assert(x1592 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1593 = x1558 - x1592;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1593 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1594 = args[2][165 * steps + ((cycle - 0) & mask)];
        assert(x1594 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1595 = x1594 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1596 = x1595 + x1588;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1597 = x1559 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1598 = x1596 - x1597;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1599 = x1598 + x1560;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1600 = Fp(x1599.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1600);
            reg = x1600;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1601 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1601 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1602 = x1599 - x1601;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1603 = x1602 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1604 = Fp(x1603.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1604);
            reg = x1604;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1605 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1605 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1606 = x1603 - x1605;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1607 = x1606 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1608 = Fp(x1607.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1608);
            reg = x1608;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1609 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1609 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1610 = x1607 - x1609;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1611 = x1610 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1611);
          reg = x1611;
        }
        if (x1590 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1612 = x1503 - x1561;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1612 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1613 = x1504 - x1562;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1613 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1614 = x1505 - x1563;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1614 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1615 = x1506 - x1564;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1615 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1616 = args[2][164 * steps + ((cycle - 0) & mask)];
      assert(x1616 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x1617 = args[2][165 * steps + ((cycle - 0) & mask)];
      assert(x1617 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x1618 = args[2][166 * steps + ((cycle - 0) & mask)];
      assert(x1618 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1619 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x1619 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1620 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x1620 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1621 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x1621 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1622 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x1622 != Fp::invalid());
      {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1623 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1623 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1624 = x1616 - x1623;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1625 = (x1624 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1626 = x7 - x1625;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][175 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1626);
          reg = x1626;
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1627 = args[2][175 * steps + ((cycle - 0) & mask)];
      assert(x1627 != Fp::invalid());
      if (x1627 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1628 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x1628 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1629 = x6 - x1628;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1629 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1630 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1630 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1631 = x1630 - x1616;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1632 = x1631 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1633 = Fp(x1632.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][25 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1633);
            reg = x1633;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1634 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x1634 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1635 = x1632 - x1634;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1636 = x1635 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1637 = Fp(x1636.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][26 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1637);
            reg = x1637;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1638 = args[2][26 * steps + ((cycle - 0) & mask)];
        assert(x1638 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1639 = x1636 - x1638;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1640 = x1639 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1641 = Fp(x1640.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][27 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1641);
            reg = x1641;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1642 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x1642 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1643 = x1640 - x1642;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1644 = x1643 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][78 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1644);
          reg = x1644;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1645 = x7 - x1627;
      if (x1645 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1646 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x1646 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1647 = x7 - x1646;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1648 = x5 - x1646;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1649 = x1647 * x1648;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1649 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1650 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1650 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1651 = x1616 - x1650;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1651 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1652 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x1652 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1653 = x1652 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1654 = x1653 + x1646;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1655 = x1617 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1656 = x1654 - x1655;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1657 = x1656 + x1618;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1658 = Fp(x1657.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][25 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1658);
            reg = x1658;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1659 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x1659 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1660 = x1657 - x1659;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1661 = x1660 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1662 = Fp(x1661.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][26 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1662);
            reg = x1662;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1663 = args[2][26 * steps + ((cycle - 0) & mask)];
        assert(x1663 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1664 = x1661 - x1663;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1665 = x1664 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1666 = Fp(x1665.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][27 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1666);
            reg = x1666;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1667 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x1667 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1668 = x1665 - x1667;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1669 = x1668 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][78 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1669);
          reg = x1669;
        }
        if (x1648 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1670 = x1561 - x1619;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1670 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1671 = x1562 - x1620;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1671 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1672 = x1563 - x1621;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1672 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1673 = x1564 - x1622;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1673 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x1674 = args[2][98 * steps + ((cycle - 0) & mask)];
    assert(x1674 != Fp::invalid());
    if (x1674 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1675 = host_outs.at(0);
        auto x1676 = host_outs.at(1);
        auto x1677 = host_outs.at(2);
        auto x1678 = host_outs.at(3);
        auto x1679 = host_outs.at(4);
        auto x1680 = host_outs.at(5);
        auto x1681 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1675);
          reg = x1675;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1676);
          reg = x1676;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1677);
          reg = x1677;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1678);
          reg = x1678;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1679);
          reg = x1679;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][141 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1680);
          reg = x1680;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1681);
          reg = x1681;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1682 = host_outs.at(0);
        auto x1683 = host_outs.at(1);
        auto x1684 = host_outs.at(2);
        auto x1685 = host_outs.at(3);
        auto x1686 = host_outs.at(4);
        auto x1687 = host_outs.at(5);
        auto x1688 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1682);
          reg = x1682;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1683);
          reg = x1683;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1684);
          reg = x1684;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1685);
          reg = x1685;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1686);
          reg = x1686;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1687);
          reg = x1687;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1688);
          reg = x1688;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1689 = host_outs.at(0);
        auto x1690 = host_outs.at(1);
        auto x1691 = host_outs.at(2);
        auto x1692 = host_outs.at(3);
        auto x1693 = host_outs.at(4);
        auto x1694 = host_outs.at(5);
        auto x1695 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1689);
          reg = x1689;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1690);
          reg = x1690;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1691);
          reg = x1691;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1692);
          reg = x1692;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1693);
          reg = x1693;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1694);
          reg = x1694;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1695);
          reg = x1695;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1696 = host_outs.at(0);
        auto x1697 = host_outs.at(1);
        auto x1698 = host_outs.at(2);
        auto x1699 = host_outs.at(3);
        auto x1700 = host_outs.at(4);
        auto x1701 = host_outs.at(5);
        auto x1702 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1696);
          reg = x1696;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1697);
          reg = x1697;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1698);
          reg = x1698;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1699);
          reg = x1699;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1700);
          reg = x1700;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1701);
          reg = x1701;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1702);
          reg = x1702;
        }
      }
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1703 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x1703 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x1704 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x1704 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x1705 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x1705 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1706 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x1706 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1707 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x1707 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1708 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x1708 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1709 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x1709 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1710 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x1710 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1711 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x1711 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1712 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x1712 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1713 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x1713 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1714 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x1714 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1715 = x1703 - x1714;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1716 = (x1715 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1717 = x7 - x1716;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1717);
          reg = x1717;
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1718 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x1718 != Fp::invalid());
      if (x1718 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1719 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x1719 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1720 = x6 - x1719;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1720 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1721 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x1721 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1722 = x1721 - x1703;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1723 = x1722 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1724 = Fp(x1723.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1724);
            reg = x1724;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1725 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1725 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1726 = x1723 - x1725;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1727 = x1726 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1728 = Fp(x1727.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1728);
            reg = x1728;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1729 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1729 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1730 = x1727 - x1729;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1731 = x1730 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1732 = Fp(x1731.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1732);
            reg = x1732;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1733 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1733 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1734 = x1731 - x1733;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1735 = x1734 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1735);
          reg = x1735;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1736 = x7 - x1718;
      if (x1736 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1737 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x1737 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1738 = x7 - x1737;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1739 = x5 - x1737;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1740 = x1738 * x1739;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1740 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1741 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x1741 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1742 = x1703 - x1741;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1742 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1743 = args[2][137 * steps + ((cycle - 0) & mask)];
        assert(x1743 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1744 = x1743 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1745 = x1744 + x1737;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1746 = x1704 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1747 = x1745 - x1746;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1748 = x1747 + x1705;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1749 = Fp(x1748.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1749);
            reg = x1749;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1750 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1750 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1751 = x1748 - x1750;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1752 = x1751 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1753 = Fp(x1752.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1753);
            reg = x1753;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1754 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1754 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1755 = x1752 - x1754;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1756 = x1755 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1757 = Fp(x1756.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1757);
            reg = x1757;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1758 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1758 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1759 = x1756 - x1758;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1760 = x1759 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1760);
          reg = x1760;
        }
        if (x1739 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1761 = x1706 - x1710;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1761 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1762 = x1707 - x1711;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1762 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1763 = x1708 - x1712;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1763 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1764 = x1709 - x1713;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1764 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1765 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x1765 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x1766 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x1766 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x1767 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x1767 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1768 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x1768 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1769 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x1769 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1770 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x1770 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1771 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x1771 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1772 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1772 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1773 = x1765 - x1772;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1774 = (x1773 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1775 = x7 - x1774;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1775);
          reg = x1775;
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1776 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x1776 != Fp::invalid());
      if (x1776 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1777 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x1777 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1778 = x6 - x1777;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1778 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1779 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1779 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1780 = x1779 - x1765;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1781 = x1780 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1782 = Fp(x1781.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1782);
            reg = x1782;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1783 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x1783 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1784 = x1781 - x1783;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1785 = x1784 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1786 = Fp(x1785.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1786);
            reg = x1786;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1787 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x1787 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1788 = x1785 - x1787;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1789 = x1788 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1790 = Fp(x1789.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1790);
            reg = x1790;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1791 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x1791 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1792 = x1789 - x1791;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1793 = x1792 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1793);
          reg = x1793;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1794 = x7 - x1776;
      if (x1794 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1795 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x1795 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1796 = x7 - x1795;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1797 = x5 - x1795;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1798 = x1796 * x1797;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1798 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1799 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1799 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1800 = x1765 - x1799;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1800 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1801 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x1801 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1802 = x1801 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1803 = x1802 + x1795;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1804 = x1766 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1805 = x1803 - x1804;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1806 = x1805 + x1767;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1807 = Fp(x1806.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1807);
            reg = x1807;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1808 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x1808 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1809 = x1806 - x1808;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1810 = x1809 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1811 = Fp(x1810.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1811);
            reg = x1811;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1812 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x1812 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1813 = x1810 - x1812;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1814 = x1813 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1815 = Fp(x1814.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1815);
            reg = x1815;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1816 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x1816 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1817 = x1814 - x1816;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1818 = x1817 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1818);
          reg = x1818;
        }
        if (x1797 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1819 = x1710 - x1768;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1819 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1820 = x1711 - x1769;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1820 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1821 = x1712 - x1770;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1821 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1822 = x1713 - x1771;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1822 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1823 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x1823 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x1824 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x1824 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x1825 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x1825 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1826 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x1826 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1827 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x1827 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1828 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x1828 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1829 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x1829 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1830 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1830 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1831 = x1823 - x1830;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1832 = (x1831 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1833 = x7 - x1832;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1833);
          reg = x1833;
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1834 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x1834 != Fp::invalid());
      if (x1834 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1835 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x1835 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1836 = x6 - x1835;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1836 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1837 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1837 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1838 = x1837 - x1823;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1839 = x1838 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1840 = Fp(x1839.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1840);
            reg = x1840;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1841 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x1841 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1842 = x1839 - x1841;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1843 = x1842 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1844 = Fp(x1843.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1844);
            reg = x1844;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1845 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x1845 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1846 = x1843 - x1845;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1847 = x1846 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1848 = Fp(x1847.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1848);
            reg = x1848;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1849 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x1849 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1850 = x1847 - x1849;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1851 = x1850 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1851);
          reg = x1851;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1852 = x7 - x1834;
      if (x1852 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1853 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x1853 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1854 = x7 - x1853;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1855 = x5 - x1853;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1856 = x1854 * x1855;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1856 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1857 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1857 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1858 = x1823 - x1857;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1858 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1859 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x1859 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1860 = x1859 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1861 = x1860 + x1853;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1862 = x1824 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1863 = x1861 - x1862;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1864 = x1863 + x1825;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1865 = Fp(x1864.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1865);
            reg = x1865;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1866 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x1866 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1867 = x1864 - x1866;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1868 = x1867 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1869 = Fp(x1868.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1869);
            reg = x1869;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1870 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x1870 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1871 = x1868 - x1870;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1872 = x1871 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1873 = Fp(x1872.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1873);
            reg = x1873;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1874 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x1874 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1875 = x1872 - x1874;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1876 = x1875 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1876);
          reg = x1876;
        }
        if (x1855 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1877 = x1768 - x1826;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1877 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1878 = x1769 - x1827;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1878 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1879 = x1770 - x1828;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1879 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1880 = x1771 - x1829;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1880 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1881 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x1881 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x1882 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x1882 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x1883 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x1883 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1884 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x1884 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1885 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x1885 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1886 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x1886 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1887 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x1887 != Fp::invalid());
      {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1888 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1888 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1889 = x1881 - x1888;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1890 = (x1889 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1891 = x7 - x1890;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1891);
          reg = x1891;
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1892 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x1892 != Fp::invalid());
      if (x1892 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1893 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x1893 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1894 = x6 - x1893;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1894 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1895 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1895 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1896 = x1895 - x1881;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1897 = x1896 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1898 = Fp(x1897.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1898);
            reg = x1898;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1899 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1899 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1900 = x1897 - x1899;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1901 = x1900 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1902 = Fp(x1901.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1902);
            reg = x1902;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1903 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1903 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1904 = x1901 - x1903;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1905 = x1904 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1906 = Fp(x1905.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1906);
            reg = x1906;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1907 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1907 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1908 = x1905 - x1907;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1909 = x1908 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1909);
          reg = x1909;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1910 = x7 - x1892;
      if (x1910 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1911 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x1911 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1912 = x7 - x1911;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1913 = x5 - x1911;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1914 = x1912 * x1913;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1914 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1915 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1915 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1916 = x1881 - x1915;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1916 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1917 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x1917 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1918 = x1917 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1919 = x1918 + x1911;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1920 = x1882 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1921 = x1919 - x1920;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1922 = x1921 + x1883;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1923 = Fp(x1922.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1923);
            reg = x1923;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1924 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1924 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1925 = x1922 - x1924;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1926 = x1925 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1927 = Fp(x1926.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1927);
            reg = x1927;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1928 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1928 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1929 = x1926 - x1928;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1930 = x1929 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1931 = Fp(x1930.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1931);
            reg = x1931;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1932 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1932 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1933 = x1930 - x1932;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1934 = x1933 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1934);
          reg = x1934;
        }
        if (x1913 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1935 = x1826 - x1884;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1935 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1936 = x1827 - x1885;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1936 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1937 = x1828 - x1886;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1937 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1938 = x1829 - x1887;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1938 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x1939 = args[2][99 * steps + ((cycle - 0) & mask)];
    assert(x1939 != Fp::invalid());
    if (x1939 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1940 = host_outs.at(0);
        auto x1941 = host_outs.at(1);
        auto x1942 = host_outs.at(2);
        auto x1943 = host_outs.at(3);
        auto x1944 = host_outs.at(4);
        auto x1945 = host_outs.at(5);
        auto x1946 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1940);
          reg = x1940;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1941);
          reg = x1941;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1942);
          reg = x1942;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1943);
          reg = x1943;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1944);
          reg = x1944;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][141 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1945);
          reg = x1945;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1946);
          reg = x1946;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1947 = host_outs.at(0);
        auto x1948 = host_outs.at(1);
        auto x1949 = host_outs.at(2);
        auto x1950 = host_outs.at(3);
        auto x1951 = host_outs.at(4);
        auto x1952 = host_outs.at(5);
        auto x1953 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1947);
          reg = x1947;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1948);
          reg = x1948;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1949);
          reg = x1949;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1950);
          reg = x1950;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1951);
          reg = x1951;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1952);
          reg = x1952;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1953);
          reg = x1953;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1954 = host_outs.at(0);
        auto x1955 = host_outs.at(1);
        auto x1956 = host_outs.at(2);
        auto x1957 = host_outs.at(3);
        auto x1958 = host_outs.at(4);
        auto x1959 = host_outs.at(5);
        auto x1960 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1954);
          reg = x1954;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1955);
          reg = x1955;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1956);
          reg = x1956;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1957);
          reg = x1957;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1958);
          reg = x1958;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1959);
          reg = x1959;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1960);
          reg = x1960;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1961 = host_outs.at(0);
        auto x1962 = host_outs.at(1);
        auto x1963 = host_outs.at(2);
        auto x1964 = host_outs.at(3);
        auto x1965 = host_outs.at(4);
        auto x1966 = host_outs.at(5);
        auto x1967 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1961);
          reg = x1961;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1962);
          reg = x1962;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1963);
          reg = x1963;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1964);
          reg = x1964;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1965);
          reg = x1965;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1966);
          reg = x1966;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1967);
          reg = x1967;
        }
      }
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1968 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x1968 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x1969 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x1969 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x1970 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x1970 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1971 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x1971 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1972 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x1972 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1973 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x1973 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1974 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x1974 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1975 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x1975 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1976 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x1976 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1977 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x1977 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1978 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x1978 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1979 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x1979 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1980 = x1968 - x1979;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1981 = (x1980 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1982 = x7 - x1981;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1982);
          reg = x1982;
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x1983 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x1983 != Fp::invalid());
      if (x1983 != 0) {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1984 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x1984 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1985 = x6 - x1984;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1985 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x1986 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x1986 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1987 = x1986 - x1968;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1988 = x1987 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1989 = Fp(x1988.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1989);
            reg = x1989;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1990 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1990 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1991 = x1988 - x1990;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1992 = x1991 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1993 = Fp(x1992.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1993);
            reg = x1993;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1994 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1994 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1995 = x1992 - x1994;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x1996 = x1995 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x1997 = Fp(x1996.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1997);
            reg = x1997;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x1998 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1998 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x1999 = x1996 - x1998;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2000 = x1999 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2000);
          reg = x2000;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2001 = x7 - x1983;
      if (x2001 != 0) {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2002 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x2002 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2003 = x7 - x2002;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2004 = x5 - x2002;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2005 = x2003 * x2004;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2005 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2006 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x2006 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2007 = x1968 - x2006;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2007 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2008 = args[2][137 * steps + ((cycle - 0) & mask)];
        assert(x2008 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2009 = x2008 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2010 = x2009 + x2002;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2011 = x1969 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2012 = x2010 - x2011;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2013 = x2012 + x1970;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2014 = Fp(x2013.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2014);
            reg = x2014;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2015 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2015 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2016 = x2013 - x2015;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2017 = x2016 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2018 = Fp(x2017.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2018);
            reg = x2018;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2019 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2019 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2020 = x2017 - x2019;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2021 = x2020 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2022 = Fp(x2021.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2022);
            reg = x2022;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2023 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2023 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2024 = x2021 - x2023;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2025 = x2024 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2025);
          reg = x2025;
        }
        if (x2004 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2026 = x1971 - x1975;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2026 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2027 = x1972 - x1976;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2027 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2028 = x1973 - x1977;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2028 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2029 = x1974 - x1978;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2029 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2030 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x2030 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x2031 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x2031 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x2032 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x2032 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2033 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x2033 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2034 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x2034 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2035 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x2035 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2036 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x2036 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2037 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x2037 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2038 = x2030 - x2037;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2039 = (x2038 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2040 = x7 - x2039;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2040);
          reg = x2040;
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2041 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x2041 != Fp::invalid());
      if (x2041 != 0) {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2042 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x2042 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2043 = x6 - x2042;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2043 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2044 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x2044 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2045 = x2044 - x2030;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2046 = x2045 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2047 = Fp(x2046.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2047);
            reg = x2047;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2048 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2048 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2049 = x2046 - x2048;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2050 = x2049 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2051 = Fp(x2050.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2051);
            reg = x2051;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2052 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2052 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2053 = x2050 - x2052;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2054 = x2053 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2055 = Fp(x2054.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2055);
            reg = x2055;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2056 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2056 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2057 = x2054 - x2056;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2058 = x2057 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2058);
          reg = x2058;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2059 = x7 - x2041;
      if (x2059 != 0) {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2060 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x2060 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2061 = x7 - x2060;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2062 = x5 - x2060;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2063 = x2061 * x2062;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2063 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2064 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x2064 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2065 = x2030 - x2064;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2065 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2066 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x2066 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2067 = x2066 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2068 = x2067 + x2060;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2069 = x2031 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2070 = x2068 - x2069;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2071 = x2070 + x2032;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2072 = Fp(x2071.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2072);
            reg = x2072;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2073 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2073 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2074 = x2071 - x2073;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2075 = x2074 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2076 = Fp(x2075.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2076);
            reg = x2076;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2077 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2077 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2078 = x2075 - x2077;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2079 = x2078 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2080 = Fp(x2079.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2080);
            reg = x2080;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2081 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2081 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2082 = x2079 - x2081;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2083 = x2082 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2083);
          reg = x2083;
        }
        if (x2062 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2084 = x1975 - x2033;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2084 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2085 = x1976 - x2034;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2085 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2086 = x1977 - x2035;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2086 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2087 = x1978 - x2036;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2087 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2088 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x2088 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x2089 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x2089 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x2090 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x2090 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2091 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x2091 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2092 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x2092 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2093 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x2093 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2094 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x2094 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2095 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x2095 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2096 = x2088 - x2095;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2097 = (x2096 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2098 = x7 - x2097;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2098);
          reg = x2098;
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2099 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x2099 != Fp::invalid());
      if (x2099 != 0) {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2100 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x2100 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2101 = x6 - x2100;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2101 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2102 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x2102 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2103 = x2102 - x2088;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2104 = x2103 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2105 = Fp(x2104.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2105);
            reg = x2105;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2106 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x2106 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2107 = x2104 - x2106;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2108 = x2107 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2109 = Fp(x2108.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2109);
            reg = x2109;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2110 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x2110 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2111 = x2108 - x2110;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2112 = x2111 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2113 = Fp(x2112.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2113);
            reg = x2113;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2114 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x2114 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2115 = x2112 - x2114;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2116 = x2115 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2116);
          reg = x2116;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2117 = x7 - x2099;
      if (x2117 != 0) {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2118 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x2118 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2119 = x7 - x2118;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2120 = x5 - x2118;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2121 = x2119 * x2120;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2121 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2122 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x2122 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2123 = x2088 - x2122;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2123 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2124 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x2124 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2125 = x2124 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2126 = x2125 + x2118;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2127 = x2089 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2128 = x2126 - x2127;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2129 = x2128 + x2090;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2130 = Fp(x2129.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2130);
            reg = x2130;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2131 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x2131 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2132 = x2129 - x2131;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2133 = x2132 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2134 = Fp(x2133.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2134);
            reg = x2134;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2135 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x2135 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2136 = x2133 - x2135;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2137 = x2136 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2138 = Fp(x2137.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2138);
            reg = x2138;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2139 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x2139 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2140 = x2137 - x2139;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2141 = x2140 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2141);
          reg = x2141;
        }
        if (x2120 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2142 = x2033 - x2091;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2142 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2143 = x2034 - x2092;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2143 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2144 = x2035 - x2093;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2144 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2145 = x2036 - x2094;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2145 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2146 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x2146 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x2147 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x2147 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x2148 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x2148 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2149 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x2149 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2150 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x2150 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2151 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x2151 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2152 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x2152 != Fp::invalid());
      {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2153 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2153 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2154 = x2146 - x2153;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2155 = (x2154 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2156 = x7 - x2155;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2156);
          reg = x2156;
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2157 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x2157 != Fp::invalid());
      if (x2157 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2158 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2158 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2159 = x6 - x2158;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2159 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2160 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2160 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2161 = x2160 - x2146;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2162 = x2161 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2163 = Fp(x2162.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2163);
            reg = x2163;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2164 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x2164 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2165 = x2162 - x2164;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2166 = x2165 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2167 = Fp(x2166.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2167);
            reg = x2167;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2168 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x2168 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2169 = x2166 - x2168;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2170 = x2169 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2171 = Fp(x2170.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2171);
            reg = x2171;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2172 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x2172 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2173 = x2170 - x2172;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2174 = x2173 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2174);
          reg = x2174;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2175 = x7 - x2157;
      if (x2175 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2176 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2176 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2177 = x7 - x2176;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2178 = x5 - x2176;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2179 = x2177 * x2178;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2179 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2180 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2180 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2181 = x2146 - x2180;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2181 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2182 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x2182 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2183 = x2182 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2184 = x2183 + x2176;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2185 = x2147 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2186 = x2184 - x2185;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2187 = x2186 + x2148;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2188 = Fp(x2187.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2188);
            reg = x2188;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2189 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x2189 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2190 = x2187 - x2189;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2191 = x2190 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2192 = Fp(x2191.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2192);
            reg = x2192;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2193 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x2193 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2194 = x2191 - x2193;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2195 = x2194 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2196 = Fp(x2195.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2196);
            reg = x2196;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2197 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x2197 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2198 = x2195 - x2197;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2199 = x2198 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2199);
          reg = x2199;
        }
        if (x2178 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2200 = x2091 - x2149;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2200 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2201 = x2092 - x2150;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2201 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2202 = x2093 - x2151;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2202 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2203 = x2094 - x2152;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2203 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x2204 = args[2][100 * steps + ((cycle - 0) & mask)];
    assert(x2204 != Fp::invalid());
    if (x2204 != 0) {
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2205 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x2205 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2206 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x2206 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2207 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x2207 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2208 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x2208 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2209 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x2209 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2210 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x2210 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2211 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x2211 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2205);
        reg = x2205;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2206);
        reg = x2206;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2207);
        reg = x2207;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2208);
        reg = x2208;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2209);
        reg = x2209;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2210);
        reg = x2210;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2211);
        reg = x2211;
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x2212 = args[2][101 * steps + ((cycle - 0) & mask)];
    assert(x2212 != Fp::invalid());
    if (x2212 != 0) {
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2213 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x2213 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2214 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x2214 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2215 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x2215 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2216 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x2216 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2217 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x2217 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2218 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x2218 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2219 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x2219 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2213);
        reg = x2213;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2214);
        reg = x2214;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2215);
        reg = x2215;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2216);
        reg = x2216;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2217);
        reg = x2217;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2218);
        reg = x2218;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2219);
        reg = x2219;
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x2220 = args[2][102 * steps + ((cycle - 0) & mask)];
    assert(x2220 != Fp::invalid());
    if (x2220 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2221 = host_outs.at(0);
        auto x2222 = host_outs.at(1);
        auto x2223 = host_outs.at(2);
        auto x2224 = host_outs.at(3);
        auto x2225 = host_outs.at(4);
        auto x2226 = host_outs.at(5);
        auto x2227 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2221);
          reg = x2221;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2222);
          reg = x2222;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2223);
          reg = x2223;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2224);
          reg = x2224;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2225);
          reg = x2225;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2226);
          reg = x2226;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2227);
          reg = x2227;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2228 = host_outs.at(0);
        auto x2229 = host_outs.at(1);
        auto x2230 = host_outs.at(2);
        auto x2231 = host_outs.at(3);
        auto x2232 = host_outs.at(4);
        auto x2233 = host_outs.at(5);
        auto x2234 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2228);
          reg = x2228;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2229);
          reg = x2229;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2230);
          reg = x2230;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2231);
          reg = x2231;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2232);
          reg = x2232;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2233);
          reg = x2233;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2234);
          reg = x2234;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2235 = host_outs.at(0);
        auto x2236 = host_outs.at(1);
        auto x2237 = host_outs.at(2);
        auto x2238 = host_outs.at(3);
        auto x2239 = host_outs.at(4);
        auto x2240 = host_outs.at(5);
        auto x2241 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2235);
          reg = x2235;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2236);
          reg = x2236;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2237);
          reg = x2237;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2238);
          reg = x2238;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][161 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2239);
          reg = x2239;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][162 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2240);
          reg = x2240;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][163 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2241);
          reg = x2241;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2242 = host_outs.at(0);
        auto x2243 = host_outs.at(1);
        auto x2244 = host_outs.at(2);
        auto x2245 = host_outs.at(3);
        auto x2246 = host_outs.at(4);
        auto x2247 = host_outs.at(5);
        auto x2248 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][164 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2242);
          reg = x2242;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][165 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2243);
          reg = x2243;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][166 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2244);
          reg = x2244;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][167 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2245);
          reg = x2245;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2246);
          reg = x2246;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][169 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2247);
          reg = x2247;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2248);
          reg = x2248;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2249 = host_outs.at(0);
        auto x2250 = host_outs.at(1);
        auto x2251 = host_outs.at(2);
        auto x2252 = host_outs.at(3);
        auto x2253 = host_outs.at(4);
        auto x2254 = host_outs.at(5);
        auto x2255 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2249);
          reg = x2249;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2250);
          reg = x2250;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2251);
          reg = x2251;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2252);
          reg = x2252;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2253);
          reg = x2253;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2254);
          reg = x2254;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2255);
          reg = x2255;
        }
      }
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2256 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x2256 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x2257 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x2257 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x2258 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x2258 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2259 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x2259 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2260 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x2260 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2261 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x2261 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2262 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x2262 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2263 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x2263 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2264 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x2264 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2265 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x2265 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2266 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x2266 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2267 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x2267 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2268 = x2256 - x2267;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2269 = (x2268 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2270 = x7 - x2269;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][171 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2270);
          reg = x2270;
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2271 = args[2][171 * steps + ((cycle - 0) & mask)];
      assert(x2271 != Fp::invalid());
      if (x2271 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2272 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x2272 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2273 = x6 - x2272;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2273 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2274 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x2274 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2275 = x2274 - x2256;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2276 = x2275 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2277 = Fp(x2276.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2277);
            reg = x2277;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2278 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2278 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2279 = x2276 - x2278;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2280 = x2279 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2281 = Fp(x2280.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2281);
            reg = x2281;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2282 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2282 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2283 = x2280 - x2282;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2284 = x2283 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2285 = Fp(x2284.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2285);
            reg = x2285;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2286 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2286 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2287 = x2284 - x2286;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2288 = x2287 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2288);
          reg = x2288;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2289 = x7 - x2271;
      if (x2289 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2290 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x2290 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2291 = x7 - x2290;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2292 = x5 - x2290;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2293 = x2291 * x2292;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2293 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2294 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x2294 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2295 = x2256 - x2294;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2295 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2296 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x2296 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2297 = x2296 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2298 = x2297 + x2290;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2299 = x2257 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2300 = x2298 - x2299;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2301 = x2300 + x2258;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2302 = Fp(x2301.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2302);
            reg = x2302;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2303 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2303 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2304 = x2301 - x2303;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2305 = x2304 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2306 = Fp(x2305.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2306);
            reg = x2306;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2307 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2307 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2308 = x2305 - x2307;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2309 = x2308 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2310 = Fp(x2309.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2310);
            reg = x2310;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2311 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2311 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2312 = x2309 - x2311;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2313 = x2312 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2313);
          reg = x2313;
        }
        if (x2292 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2314 = x2259 - x2263;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2314 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2315 = x2260 - x2264;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2315 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2316 = x2261 - x2265;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2316 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2317 = x2262 - x2266;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2317 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2318 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x2318 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x2319 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x2319 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x2320 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x2320 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2321 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x2321 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2322 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x2322 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2323 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x2323 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2324 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x2324 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2325 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x2325 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2326 = x2318 - x2325;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2327 = (x2326 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2328 = x7 - x2327;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2328);
          reg = x2328;
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2329 = args[2][172 * steps + ((cycle - 0) & mask)];
      assert(x2329 != Fp::invalid());
      if (x2329 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2330 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x2330 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2331 = x6 - x2330;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2331 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2332 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x2332 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2333 = x2332 - x2318;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2334 = x2333 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2335 = Fp(x2334.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2335);
            reg = x2335;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2336 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2336 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2337 = x2334 - x2336;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2338 = x2337 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2339 = Fp(x2338.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2339);
            reg = x2339;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2340 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2340 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2341 = x2338 - x2340;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2342 = x2341 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2343 = Fp(x2342.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2343);
            reg = x2343;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2344 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2344 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2345 = x2342 - x2344;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2346 = x2345 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2346);
          reg = x2346;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2347 = x7 - x2329;
      if (x2347 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2348 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x2348 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2349 = x7 - x2348;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2350 = x5 - x2348;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2351 = x2349 * x2350;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2351 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2352 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x2352 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2353 = x2318 - x2352;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2353 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2354 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x2354 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2355 = x2354 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2356 = x2355 + x2348;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2357 = x2319 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2358 = x2356 - x2357;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2359 = x2358 + x2320;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2360 = Fp(x2359.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2360);
            reg = x2360;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2361 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2361 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2362 = x2359 - x2361;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2363 = x2362 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2364 = Fp(x2363.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2364);
            reg = x2364;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2365 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2365 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2366 = x2363 - x2365;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2367 = x2366 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2368 = Fp(x2367.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2368);
            reg = x2368;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2369 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2369 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2370 = x2367 - x2369;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2371 = x2370 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2371);
          reg = x2371;
        }
        if (x2350 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2372 = x2263 - x2321;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2372 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2373 = x2264 - x2322;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2373 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2374 = x2265 - x2323;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2374 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2375 = x2266 - x2324;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2375 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2376 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x2376 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x2377 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x2377 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x2378 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x2378 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2379 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x2379 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2380 = args[2][161 * steps + ((cycle - 0) & mask)];
      assert(x2380 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2381 = args[2][162 * steps + ((cycle - 0) & mask)];
      assert(x2381 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2382 = args[2][163 * steps + ((cycle - 0) & mask)];
      assert(x2382 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2383 = args[2][157 * steps + ((cycle - 0) & mask)];
        assert(x2383 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2384 = x2376 - x2383;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2385 = (x2384 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2386 = x7 - x2385;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][173 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2386);
          reg = x2386;
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2387 = args[2][173 * steps + ((cycle - 0) & mask)];
      assert(x2387 != Fp::invalid());
      if (x2387 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2388 = args[2][159 * steps + ((cycle - 0) & mask)];
        assert(x2388 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2389 = x6 - x2388;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2389 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2390 = args[2][157 * steps + ((cycle - 0) & mask)];
        assert(x2390 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2391 = x2390 - x2376;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2392 = x2391 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2393 = Fp(x2392.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2393);
            reg = x2393;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2394 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x2394 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2395 = x2392 - x2394;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2396 = x2395 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2397 = Fp(x2396.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2397);
            reg = x2397;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2398 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x2398 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2399 = x2396 - x2398;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2400 = x2399 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2401 = Fp(x2400.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2401);
            reg = x2401;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2402 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x2402 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2403 = x2400 - x2402;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2404 = x2403 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2404);
          reg = x2404;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2405 = x7 - x2387;
      if (x2405 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2406 = args[2][159 * steps + ((cycle - 0) & mask)];
        assert(x2406 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2407 = x7 - x2406;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2408 = x5 - x2406;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2409 = x2407 * x2408;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2409 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2410 = args[2][157 * steps + ((cycle - 0) & mask)];
        assert(x2410 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2411 = x2376 - x2410;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2411 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2412 = args[2][158 * steps + ((cycle - 0) & mask)];
        assert(x2412 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2413 = x2412 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2414 = x2413 + x2406;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2415 = x2377 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2416 = x2414 - x2415;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2417 = x2416 + x2378;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2418 = Fp(x2417.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2418);
            reg = x2418;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2419 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x2419 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2420 = x2417 - x2419;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2421 = x2420 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2422 = Fp(x2421.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2422);
            reg = x2422;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2423 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x2423 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2424 = x2421 - x2423;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2425 = x2424 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2426 = Fp(x2425.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2426);
            reg = x2426;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2427 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x2427 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2428 = x2425 - x2427;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2429 = x2428 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2429);
          reg = x2429;
        }
        if (x2408 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2430 = x2321 - x2379;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2430 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2431 = x2322 - x2380;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2431 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2432 = x2323 - x2381;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2432 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2433 = x2324 - x2382;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2433 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2434 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x2434 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x2435 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x2435 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x2436 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x2436 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2437 = args[2][167 * steps + ((cycle - 0) & mask)];
      assert(x2437 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2438 = args[2][168 * steps + ((cycle - 0) & mask)];
      assert(x2438 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2439 = args[2][169 * steps + ((cycle - 0) & mask)];
      assert(x2439 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2440 = args[2][170 * steps + ((cycle - 0) & mask)];
      assert(x2440 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2441 = args[2][164 * steps + ((cycle - 0) & mask)];
        assert(x2441 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2442 = x2434 - x2441;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2443 = (x2442 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2444 = x7 - x2443;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][174 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2444);
          reg = x2444;
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2445 = args[2][174 * steps + ((cycle - 0) & mask)];
      assert(x2445 != Fp::invalid());
      if (x2445 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2446 = args[2][166 * steps + ((cycle - 0) & mask)];
        assert(x2446 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2447 = x6 - x2446;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2447 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2448 = args[2][164 * steps + ((cycle - 0) & mask)];
        assert(x2448 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2449 = x2448 - x2434;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2450 = x2449 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2451 = Fp(x2450.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2451);
            reg = x2451;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2452 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x2452 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2453 = x2450 - x2452;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2454 = x2453 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2455 = Fp(x2454.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2455);
            reg = x2455;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2456 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x2456 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2457 = x2454 - x2456;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2458 = x2457 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2459 = Fp(x2458.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2459);
            reg = x2459;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2460 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x2460 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2461 = x2458 - x2460;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2462 = x2461 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2462);
          reg = x2462;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2463 = x7 - x2445;
      if (x2463 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2464 = args[2][166 * steps + ((cycle - 0) & mask)];
        assert(x2464 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2465 = x7 - x2464;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2466 = x5 - x2464;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2467 = x2465 * x2466;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2467 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2468 = args[2][164 * steps + ((cycle - 0) & mask)];
        assert(x2468 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2469 = x2434 - x2468;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2469 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2470 = args[2][165 * steps + ((cycle - 0) & mask)];
        assert(x2470 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2471 = x2470 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2472 = x2471 + x2464;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2473 = x2435 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2474 = x2472 - x2473;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2475 = x2474 + x2436;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2476 = Fp(x2475.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2476);
            reg = x2476;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2477 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x2477 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2478 = x2475 - x2477;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2479 = x2478 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2480 = Fp(x2479.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2480);
            reg = x2480;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2481 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x2481 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2482 = x2479 - x2481;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2483 = x2482 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2484 = Fp(x2483.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2484);
            reg = x2484;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2485 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x2485 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2486 = x2483 - x2485;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2487 = x2486 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2487);
          reg = x2487;
        }
        if (x2466 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2488 = x2379 - x2437;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2488 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2489 = x2380 - x2438;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2489 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2490 = x2381 - x2439;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2490 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2491 = x2382 - x2440;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2491 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2492 = args[2][164 * steps + ((cycle - 0) & mask)];
      assert(x2492 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x2493 = args[2][165 * steps + ((cycle - 0) & mask)];
      assert(x2493 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x2494 = args[2][166 * steps + ((cycle - 0) & mask)];
      assert(x2494 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2495 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x2495 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2496 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x2496 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2497 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x2497 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2498 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x2498 != Fp::invalid());
      {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2499 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2499 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2500 = x2492 - x2499;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2501 = (x2500 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2502 = x7 - x2501;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][175 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2502);
          reg = x2502;
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2503 = args[2][175 * steps + ((cycle - 0) & mask)];
      assert(x2503 != Fp::invalid());
      if (x2503 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2504 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2504 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2505 = x6 - x2504;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2505 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2506 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2506 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2507 = x2506 - x2492;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2508 = x2507 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2509 = Fp(x2508.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][25 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2509);
            reg = x2509;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2510 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x2510 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2511 = x2508 - x2510;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2512 = x2511 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2513 = Fp(x2512.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][26 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2513);
            reg = x2513;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2514 = args[2][26 * steps + ((cycle - 0) & mask)];
        assert(x2514 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2515 = x2512 - x2514;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2516 = x2515 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2517 = Fp(x2516.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][27 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2517);
            reg = x2517;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2518 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x2518 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2519 = x2516 - x2518;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2520 = x2519 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][78 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2520);
          reg = x2520;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2521 = x7 - x2503;
      if (x2521 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2522 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2522 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2523 = x7 - x2522;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2524 = x5 - x2522;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2525 = x2523 * x2524;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2525 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2526 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2526 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2527 = x2492 - x2526;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2527 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2528 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x2528 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2529 = x2528 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2530 = x2529 + x2522;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2531 = x2493 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2532 = x2530 - x2531;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2533 = x2532 + x2494;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2534 = Fp(x2533.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][25 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2534);
            reg = x2534;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2535 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x2535 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2536 = x2533 - x2535;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2537 = x2536 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2538 = Fp(x2537.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][26 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2538);
            reg = x2538;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2539 = args[2][26 * steps + ((cycle - 0) & mask)];
        assert(x2539 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2540 = x2537 - x2539;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2541 = x2540 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2542 = Fp(x2541.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][27 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2542);
            reg = x2542;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2543 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x2543 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2544 = x2541 - x2543;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2545 = x2544 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][78 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2545);
          reg = x2545;
        }
        if (x2524 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2546 = x2437 - x2495;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2546 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2547 = x2438 - x2496;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2547 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2548 = x2439 - x2497;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2548 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2549 = x2440 - x2498;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2549 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x2550 = args[2][103 * steps + ((cycle - 0) & mask)];
    assert(x2550 != Fp::invalid());
    if (x2550 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2551 = host_outs.at(0);
        auto x2552 = host_outs.at(1);
        auto x2553 = host_outs.at(2);
        auto x2554 = host_outs.at(3);
        auto x2555 = host_outs.at(4);
        auto x2556 = host_outs.at(5);
        auto x2557 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][122 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2551);
          reg = x2551;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][123 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2552);
          reg = x2552;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][124 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2553);
          reg = x2553;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][125 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2554);
          reg = x2554;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][126 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2555);
          reg = x2555;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][127 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2556);
          reg = x2556;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][128 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2557);
          reg = x2557;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2558 = host_outs.at(0);
        auto x2559 = host_outs.at(1);
        auto x2560 = host_outs.at(2);
        auto x2561 = host_outs.at(3);
        auto x2562 = host_outs.at(4);
        auto x2563 = host_outs.at(5);
        auto x2564 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2558);
          reg = x2558;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2559);
          reg = x2559;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2560);
          reg = x2560;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2561);
          reg = x2561;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2562);
          reg = x2562;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2563);
          reg = x2563;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2564);
          reg = x2564;
        }
      }
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2565 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x2565 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x2566 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x2566 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x2567 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x2567 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2568 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x2568 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2569 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x2569 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2570 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x2570 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2571 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x2571 != Fp::invalid());
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2572 = args[2][125 * steps + ((cycle - 0) & mask)];
      assert(x2572 != Fp::invalid());
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2573 = args[2][126 * steps + ((cycle - 0) & mask)];
      assert(x2573 != Fp::invalid());
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2574 = args[2][127 * steps + ((cycle - 0) & mask)];
      assert(x2574 != Fp::invalid());
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2575 = args[2][128 * steps + ((cycle - 0) & mask)];
      assert(x2575 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2576 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x2576 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2577 = x2565 - x2576;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2578 = (x2577 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2579 = x7 - x2578;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][129 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2579);
          reg = x2579;
        }
      }
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2580 = args[2][129 * steps + ((cycle - 0) & mask)];
      assert(x2580 != Fp::invalid());
      if (x2580 != 0) {
        // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2581 = args[2][124 * steps + ((cycle - 0) & mask)];
        assert(x2581 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2582 = x6 - x2581;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2582 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2583 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x2583 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2584 = x2583 - x2565;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2585 = x2584 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2586 = Fp(x2585.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2586);
            reg = x2586;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2587 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2587 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2588 = x2585 - x2587;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2589 = x2588 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2590 = Fp(x2589.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2590);
            reg = x2590;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2591 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2591 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2592 = x2589 - x2591;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2593 = x2592 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2594 = Fp(x2593.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2594);
            reg = x2594;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2595 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2595 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2596 = x2593 - x2595;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2597 = x2596 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2597);
          reg = x2597;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2598 = x7 - x2580;
      if (x2598 != 0) {
        // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2599 = args[2][124 * steps + ((cycle - 0) & mask)];
        assert(x2599 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2600 = x7 - x2599;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2601 = x5 - x2599;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2602 = x2600 * x2601;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2602 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2603 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x2603 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2604 = x2565 - x2603;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2604 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2605 = args[2][123 * steps + ((cycle - 0) & mask)];
        assert(x2605 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2606 = x2605 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2607 = x2606 + x2599;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2608 = x2566 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2609 = x2607 - x2608;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2610 = x2609 + x2567;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2611 = Fp(x2610.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2611);
            reg = x2611;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2612 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2612 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2613 = x2610 - x2612;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2614 = x2613 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2615 = Fp(x2614.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2615);
            reg = x2615;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2616 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2616 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2617 = x2614 - x2616;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2618 = x2617 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2619 = Fp(x2618.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2619);
            reg = x2619;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2620 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2620 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2621 = x2618 - x2620;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2622 = x2621 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2622);
          reg = x2622;
        }
        if (x2601 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2623 = x2568 - x2572;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2623 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2624 = x2569 - x2573;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2624 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2625 = x2570 - x2574;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2625 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2626 = x2571 - x2575;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2626 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2627 = args[2][122 * steps + ((cycle - 0) & mask)];
      assert(x2627 != Fp::invalid());
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x2628 = args[2][123 * steps + ((cycle - 0) & mask)];
      assert(x2628 != Fp::invalid());
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x2629 = args[2][124 * steps + ((cycle - 0) & mask)];
      assert(x2629 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2630 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x2630 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2631 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x2631 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2632 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x2632 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2633 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x2633 != Fp::invalid());
      {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2634 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2634 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2635 = x2627 - x2634;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2636 = (x2635 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2637 = x7 - x2636;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][130 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2637);
          reg = x2637;
        }
      }
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2638 = args[2][130 * steps + ((cycle - 0) & mask)];
      assert(x2638 != Fp::invalid());
      if (x2638 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2639 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2639 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2640 = x6 - x2639;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2640 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2641 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2641 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2642 = x2641 - x2627;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2643 = x2642 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2644 = Fp(x2643.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2644);
            reg = x2644;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2645 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2645 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2646 = x2643 - x2645;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2647 = x2646 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2648 = Fp(x2647.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2648);
            reg = x2648;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2649 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2649 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2650 = x2647 - x2649;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2651 = x2650 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2652 = Fp(x2651.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2652);
            reg = x2652;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2653 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2653 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2654 = x2651 - x2653;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2655 = x2654 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2655);
          reg = x2655;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2656 = x7 - x2638;
      if (x2656 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2657 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2657 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2658 = x7 - x2657;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2659 = x5 - x2657;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2660 = x2658 * x2659;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2660 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2661 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2661 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2662 = x2627 - x2661;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2662 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2663 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x2663 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2664 = x2663 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2665 = x2664 + x2657;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2666 = x2628 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2667 = x2665 - x2666;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2668 = x2667 + x2629;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2669 = Fp(x2668.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2669);
            reg = x2669;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2670 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2670 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2671 = x2668 - x2670;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2672 = x2671 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2673 = Fp(x2672.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2673);
            reg = x2673;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2674 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2674 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2675 = x2672 - x2674;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2676 = x2675 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2677 = Fp(x2676.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2677);
            reg = x2677;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2678 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2678 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2679 = x2676 - x2678;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2680 = x2679 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2680);
          reg = x2680;
        }
        if (x2659 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2681 = x2572 - x2630;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2681 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2682 = x2573 - x2631;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2682 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2683 = x2574 - x2632;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2683 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2684 = x2575 - x2633;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2684 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x2685 = args[2][104 * steps + ((cycle - 0) & mask)];
    assert(x2685 != Fp::invalid());
    if (x2685 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2686 = host_outs.at(0);
        auto x2687 = host_outs.at(1);
        auto x2688 = host_outs.at(2);
        auto x2689 = host_outs.at(3);
        auto x2690 = host_outs.at(4);
        auto x2691 = host_outs.at(5);
        auto x2692 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][122 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2686);
          reg = x2686;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][123 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2687);
          reg = x2687;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][124 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2688);
          reg = x2688;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][125 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2689);
          reg = x2689;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][126 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2690);
          reg = x2690;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][127 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2691);
          reg = x2691;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][128 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2692);
          reg = x2692;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2693 = host_outs.at(0);
        auto x2694 = host_outs.at(1);
        auto x2695 = host_outs.at(2);
        auto x2696 = host_outs.at(3);
        auto x2697 = host_outs.at(4);
        auto x2698 = host_outs.at(5);
        auto x2699 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2693);
          reg = x2693;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2694);
          reg = x2694;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2695);
          reg = x2695;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2696);
          reg = x2696;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2697);
          reg = x2697;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2698);
          reg = x2698;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2699);
          reg = x2699;
        }
      }
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2700 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x2700 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x2701 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x2701 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x2702 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x2702 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2703 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x2703 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2704 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x2704 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2705 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x2705 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2706 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x2706 != Fp::invalid());
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2707 = args[2][125 * steps + ((cycle - 0) & mask)];
      assert(x2707 != Fp::invalid());
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2708 = args[2][126 * steps + ((cycle - 0) & mask)];
      assert(x2708 != Fp::invalid());
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2709 = args[2][127 * steps + ((cycle - 0) & mask)];
      assert(x2709 != Fp::invalid());
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2710 = args[2][128 * steps + ((cycle - 0) & mask)];
      assert(x2710 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2711 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x2711 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2712 = x2700 - x2711;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2713 = (x2712 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2714 = x7 - x2713;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][129 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2714);
          reg = x2714;
        }
      }
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2715 = args[2][129 * steps + ((cycle - 0) & mask)];
      assert(x2715 != Fp::invalid());
      if (x2715 != 0) {
        // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2716 = args[2][124 * steps + ((cycle - 0) & mask)];
        assert(x2716 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2717 = x6 - x2716;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2717 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2718 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x2718 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2719 = x2718 - x2700;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2720 = x2719 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2721 = Fp(x2720.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2721);
            reg = x2721;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2722 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2722 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2723 = x2720 - x2722;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2724 = x2723 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2725 = Fp(x2724.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2725);
            reg = x2725;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2726 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2726 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2727 = x2724 - x2726;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2728 = x2727 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2729 = Fp(x2728.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2729);
            reg = x2729;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2730 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2730 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2731 = x2728 - x2730;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2732 = x2731 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2732);
          reg = x2732;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2733 = x7 - x2715;
      if (x2733 != 0) {
        // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2734 = args[2][124 * steps + ((cycle - 0) & mask)];
        assert(x2734 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2735 = x7 - x2734;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2736 = x5 - x2734;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2737 = x2735 * x2736;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2737 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2738 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x2738 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2739 = x2700 - x2738;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2739 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2740 = args[2][123 * steps + ((cycle - 0) & mask)];
        assert(x2740 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2741 = x2740 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2742 = x2741 + x2734;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2743 = x2701 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2744 = x2742 - x2743;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2745 = x2744 + x2702;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2746 = Fp(x2745.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2746);
            reg = x2746;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2747 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2747 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2748 = x2745 - x2747;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2749 = x2748 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2750 = Fp(x2749.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2750);
            reg = x2750;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2751 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2751 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2752 = x2749 - x2751;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2753 = x2752 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2754 = Fp(x2753.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2754);
            reg = x2754;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2755 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2755 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2756 = x2753 - x2755;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2757 = x2756 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2757);
          reg = x2757;
        }
        if (x2736 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2758 = x2703 - x2707;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2758 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2759 = x2704 - x2708;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2759 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2760 = x2705 - x2709;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2760 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2761 = x2706 - x2710;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2761 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2762 = args[2][122 * steps + ((cycle - 0) & mask)];
      assert(x2762 != Fp::invalid());
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x2763 = args[2][123 * steps + ((cycle - 0) & mask)];
      assert(x2763 != Fp::invalid());
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x2764 = args[2][124 * steps + ((cycle - 0) & mask)];
      assert(x2764 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2765 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x2765 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2766 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x2766 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2767 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x2767 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2768 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x2768 != Fp::invalid());
      {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2769 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2769 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2770 = x2762 - x2769;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2771 = (x2770 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2772 = x7 - x2771;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][130 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2772);
          reg = x2772;
        }
      }
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2773 = args[2][130 * steps + ((cycle - 0) & mask)];
      assert(x2773 != Fp::invalid());
      if (x2773 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2774 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2774 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2775 = x6 - x2774;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2775 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2776 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2776 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2777 = x2776 - x2762;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2778 = x2777 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2779 = Fp(x2778.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2779);
            reg = x2779;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2780 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2780 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2781 = x2778 - x2780;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2782 = x2781 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2783 = Fp(x2782.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2783);
            reg = x2783;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2784 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2784 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2785 = x2782 - x2784;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2786 = x2785 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2787 = Fp(x2786.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2787);
            reg = x2787;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2788 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2788 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2789 = x2786 - x2788;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2790 = x2789 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2790);
          reg = x2790;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2791 = x7 - x2773;
      if (x2791 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2792 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2792 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2793 = x7 - x2792;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2794 = x5 - x2792;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2795 = x2793 * x2794;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2795 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2796 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2796 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2797 = x2762 - x2796;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2797 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2798 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x2798 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2799 = x2798 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2800 = x2799 + x2792;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2801 = x2763 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2802 = x2800 - x2801;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2803 = x2802 + x2764;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2804 = Fp(x2803.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2804);
            reg = x2804;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2805 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2805 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2806 = x2803 - x2805;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2807 = x2806 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2808 = Fp(x2807.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2808);
            reg = x2808;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2809 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2809 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2810 = x2807 - x2809;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2811 = x2810 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2812 = Fp(x2811.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2812);
            reg = x2812;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2813 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2813 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2814 = x2811 - x2813;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2815 = x2814 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2815);
          reg = x2815;
        }
        if (x2794 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2816 = x2707 - x2765;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2816 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2817 = x2708 - x2766;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2817 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2818 = x2709 - x2767;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2818 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2819 = x2710 - x2768;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2819 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x2820 = args[2][105 * steps + ((cycle - 0) & mask)];
    assert(x2820 != Fp::invalid());
    if (x2820 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2821 = host_outs.at(0);
        auto x2822 = host_outs.at(1);
        auto x2823 = host_outs.at(2);
        auto x2824 = host_outs.at(3);
        auto x2825 = host_outs.at(4);
        auto x2826 = host_outs.at(5);
        auto x2827 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][122 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2821);
          reg = x2821;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][123 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2822);
          reg = x2822;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][124 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2823);
          reg = x2823;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][125 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2824);
          reg = x2824;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][126 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2825);
          reg = x2825;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][127 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2826);
          reg = x2826;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][128 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2827);
          reg = x2827;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2828 = host_outs.at(0);
        auto x2829 = host_outs.at(1);
        auto x2830 = host_outs.at(2);
        auto x2831 = host_outs.at(3);
        auto x2832 = host_outs.at(4);
        auto x2833 = host_outs.at(5);
        auto x2834 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2828);
          reg = x2828;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2829);
          reg = x2829;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2830);
          reg = x2830;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2831);
          reg = x2831;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2832);
          reg = x2832;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2833);
          reg = x2833;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2834);
          reg = x2834;
        }
      }
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2835 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x2835 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x2836 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x2836 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x2837 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x2837 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2838 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x2838 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2839 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x2839 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2840 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x2840 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2841 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x2841 != Fp::invalid());
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2842 = args[2][125 * steps + ((cycle - 0) & mask)];
      assert(x2842 != Fp::invalid());
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2843 = args[2][126 * steps + ((cycle - 0) & mask)];
      assert(x2843 != Fp::invalid());
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2844 = args[2][127 * steps + ((cycle - 0) & mask)];
      assert(x2844 != Fp::invalid());
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2845 = args[2][128 * steps + ((cycle - 0) & mask)];
      assert(x2845 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2846 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x2846 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2847 = x2835 - x2846;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2848 = (x2847 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2849 = x7 - x2848;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][129 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2849);
          reg = x2849;
        }
      }
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2850 = args[2][129 * steps + ((cycle - 0) & mask)];
      assert(x2850 != Fp::invalid());
      if (x2850 != 0) {
        // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2851 = args[2][124 * steps + ((cycle - 0) & mask)];
        assert(x2851 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2852 = x6 - x2851;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2852 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2853 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x2853 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2854 = x2853 - x2835;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2855 = x2854 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2856 = Fp(x2855.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2856);
            reg = x2856;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2857 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2857 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2858 = x2855 - x2857;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2859 = x2858 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2860 = Fp(x2859.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2860);
            reg = x2860;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2861 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2861 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2862 = x2859 - x2861;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2863 = x2862 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2864 = Fp(x2863.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2864);
            reg = x2864;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2865 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2865 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2866 = x2863 - x2865;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2867 = x2866 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2867);
          reg = x2867;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2868 = x7 - x2850;
      if (x2868 != 0) {
        // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2869 = args[2][124 * steps + ((cycle - 0) & mask)];
        assert(x2869 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2870 = x7 - x2869;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2871 = x5 - x2869;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2872 = x2870 * x2871;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2872 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2873 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x2873 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2874 = x2835 - x2873;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2874 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2875 = args[2][123 * steps + ((cycle - 0) & mask)];
        assert(x2875 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2876 = x2875 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2877 = x2876 + x2869;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2878 = x2836 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2879 = x2877 - x2878;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2880 = x2879 + x2837;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2881 = Fp(x2880.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2881);
            reg = x2881;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2882 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2882 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2883 = x2880 - x2882;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2884 = x2883 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2885 = Fp(x2884.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2885);
            reg = x2885;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2886 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2886 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2887 = x2884 - x2886;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2888 = x2887 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2889 = Fp(x2888.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2889);
            reg = x2889;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2890 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2890 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2891 = x2888 - x2890;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2892 = x2891 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2892);
          reg = x2892;
        }
        if (x2871 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2893 = x2838 - x2842;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2893 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2894 = x2839 - x2843;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2894 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2895 = x2840 - x2844;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2895 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2896 = x2841 - x2845;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2896 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2897 = args[2][122 * steps + ((cycle - 0) & mask)];
      assert(x2897 != Fp::invalid());
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x2898 = args[2][123 * steps + ((cycle - 0) & mask)];
      assert(x2898 != Fp::invalid());
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x2899 = args[2][124 * steps + ((cycle - 0) & mask)];
      assert(x2899 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2900 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x2900 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2901 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x2901 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2902 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x2902 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2903 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x2903 != Fp::invalid());
      {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2904 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2904 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2905 = x2897 - x2904;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2906 = (x2905 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2907 = x7 - x2906;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][130 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2907);
          reg = x2907;
        }
      }
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2908 = args[2][130 * steps + ((cycle - 0) & mask)];
      assert(x2908 != Fp::invalid());
      if (x2908 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2909 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2909 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2910 = x6 - x2909;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2910 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2911 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2911 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2912 = x2911 - x2897;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2913 = x2912 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2914 = Fp(x2913.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2914);
            reg = x2914;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2915 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2915 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2916 = x2913 - x2915;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2917 = x2916 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2918 = Fp(x2917.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2918);
            reg = x2918;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2919 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2919 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2920 = x2917 - x2919;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2921 = x2920 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2922 = Fp(x2921.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2922);
            reg = x2922;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2923 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2923 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2924 = x2921 - x2923;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2925 = x2924 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2925);
          reg = x2925;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2926 = x7 - x2908;
      if (x2926 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2927 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2927 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2928 = x7 - x2927;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2929 = x5 - x2927;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2930 = x2928 * x2929;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2930 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2931 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2931 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2932 = x2897 - x2931;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2932 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2933 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x2933 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2934 = x2933 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2935 = x2934 + x2927;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2936 = x2898 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2937 = x2935 - x2936;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2938 = x2937 + x2899;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2939 = Fp(x2938.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2939);
            reg = x2939;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2940 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2940 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2941 = x2938 - x2940;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2942 = x2941 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2943 = Fp(x2942.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2943);
            reg = x2943;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2944 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2944 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2945 = x2942 - x2944;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2946 = x2945 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x2947 = Fp(x2946.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2947);
            reg = x2947;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x2948 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2948 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x2949 = x2946 - x2948;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x2950 = x2949 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2950);
          reg = x2950;
        }
        if (x2929 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2951 = x2842 - x2900;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2951 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2952 = x2843 - x2901;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2952 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2953 = x2844 - x2902;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2953 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2954 = x2845 - x2903;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2954 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x2955 = args[2][106 * steps + ((cycle - 0) & mask)];
    assert(x2955 != Fp::invalid());
    if (x2955 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2956 = host_outs.at(0);
        auto x2957 = host_outs.at(1);
        auto x2958 = host_outs.at(2);
        auto x2959 = host_outs.at(3);
        auto x2960 = host_outs.at(4);
        auto x2961 = host_outs.at(5);
        auto x2962 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2956);
          reg = x2956;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2957);
          reg = x2957;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2958);
          reg = x2958;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2959);
          reg = x2959;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2960);
          reg = x2960;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][141 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2961);
          reg = x2961;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2962);
          reg = x2962;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2963 = host_outs.at(0);
        auto x2964 = host_outs.at(1);
        auto x2965 = host_outs.at(2);
        auto x2966 = host_outs.at(3);
        auto x2967 = host_outs.at(4);
        auto x2968 = host_outs.at(5);
        auto x2969 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2963);
          reg = x2963;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2964);
          reg = x2964;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2965);
          reg = x2965;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2966);
          reg = x2966;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2967);
          reg = x2967;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2968);
          reg = x2968;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2969);
          reg = x2969;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2970 = host_outs.at(0);
        auto x2971 = host_outs.at(1);
        auto x2972 = host_outs.at(2);
        auto x2973 = host_outs.at(3);
        auto x2974 = host_outs.at(4);
        auto x2975 = host_outs.at(5);
        auto x2976 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2970);
          reg = x2970;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2971);
          reg = x2971;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2972);
          reg = x2972;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2973);
          reg = x2973;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2974);
          reg = x2974;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2975);
          reg = x2975;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2976);
          reg = x2976;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2977 = host_outs.at(0);
        auto x2978 = host_outs.at(1);
        auto x2979 = host_outs.at(2);
        auto x2980 = host_outs.at(3);
        auto x2981 = host_outs.at(4);
        auto x2982 = host_outs.at(5);
        auto x2983 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2977);
          reg = x2977;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2978);
          reg = x2978;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2979);
          reg = x2979;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2980);
          reg = x2980;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2981);
          reg = x2981;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2982);
          reg = x2982;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2983);
          reg = x2983;
        }
      }
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2984 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x2984 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x2985 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x2985 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x2986 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x2986 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2987 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x2987 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2988 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x2988 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2989 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x2989 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2990 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x2990 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2991 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x2991 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2992 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x2992 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2993 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x2993 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2994 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x2994 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x2995 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x2995 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2996 = x2984 - x2995;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2997 = (x2996 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2998 = x7 - x2997;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2998);
          reg = x2998;
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x2999 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x2999 != Fp::invalid());
      if (x2999 != 0) {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3000 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x3000 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x3001 = x6 - x3000;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x3001 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3002 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x3002 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3003 = x3002 - x2984;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3004 = x3003 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3005 = Fp(x3004.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3005);
            reg = x3005;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3006 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x3006 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3007 = x3004 - x3006;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3008 = x3007 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3009 = Fp(x3008.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3009);
            reg = x3009;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3010 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x3010 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3011 = x3008 - x3010;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3012 = x3011 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3013 = Fp(x3012.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3013);
            reg = x3013;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3014 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x3014 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3015 = x3012 - x3014;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3016 = x3015 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3016);
          reg = x3016;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x3017 = x7 - x2999;
      if (x3017 != 0) {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3018 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x3018 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x3019 = x7 - x3018;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x3020 = x5 - x3018;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x3021 = x3019 * x3020;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x3021 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3022 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x3022 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x3023 = x2984 - x3022;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x3023 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3024 = args[2][137 * steps + ((cycle - 0) & mask)];
        assert(x3024 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3025 = x3024 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3026 = x3025 + x3018;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3027 = x2985 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3028 = x3026 - x3027;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3029 = x3028 + x2986;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3030 = Fp(x3029.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3030);
            reg = x3030;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3031 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x3031 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3032 = x3029 - x3031;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3033 = x3032 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3034 = Fp(x3033.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3034);
            reg = x3034;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3035 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x3035 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3036 = x3033 - x3035;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3037 = x3036 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3038 = Fp(x3037.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3038);
            reg = x3038;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3039 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x3039 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3040 = x3037 - x3039;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3041 = x3040 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3041);
          reg = x3041;
        }
        if (x3020 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3042 = x2987 - x2991;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3042 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3043 = x2988 - x2992;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3043 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3044 = x2989 - x2993;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3044 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3045 = x2990 - x2994;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3045 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x3046 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x3046 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x3047 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x3047 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x3048 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x3048 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3049 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x3049 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3050 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x3050 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3051 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x3051 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3052 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x3052 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3053 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x3053 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3054 = x3046 - x3053;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3055 = (x3054 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x3056 = x7 - x3055;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3056);
          reg = x3056;
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3057 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x3057 != Fp::invalid());
      if (x3057 != 0) {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3058 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x3058 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x3059 = x6 - x3058;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x3059 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3060 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x3060 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3061 = x3060 - x3046;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3062 = x3061 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3063 = Fp(x3062.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3063);
            reg = x3063;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3064 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x3064 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3065 = x3062 - x3064;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3066 = x3065 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3067 = Fp(x3066.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3067);
            reg = x3067;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3068 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x3068 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3069 = x3066 - x3068;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3070 = x3069 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3071 = Fp(x3070.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3071);
            reg = x3071;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3072 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x3072 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3073 = x3070 - x3072;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3074 = x3073 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3074);
          reg = x3074;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x3075 = x7 - x3057;
      if (x3075 != 0) {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3076 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x3076 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x3077 = x7 - x3076;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x3078 = x5 - x3076;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x3079 = x3077 * x3078;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x3079 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3080 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x3080 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x3081 = x3046 - x3080;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x3081 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3082 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x3082 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3083 = x3082 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3084 = x3083 + x3076;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3085 = x3047 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3086 = x3084 - x3085;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3087 = x3086 + x3048;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3088 = Fp(x3087.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3088);
            reg = x3088;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3089 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x3089 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3090 = x3087 - x3089;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3091 = x3090 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3092 = Fp(x3091.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3092);
            reg = x3092;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3093 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x3093 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3094 = x3091 - x3093;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3095 = x3094 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3096 = Fp(x3095.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3096);
            reg = x3096;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3097 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x3097 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3098 = x3095 - x3097;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3099 = x3098 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3099);
          reg = x3099;
        }
        if (x3078 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3100 = x2991 - x3049;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3100 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3101 = x2992 - x3050;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3101 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3102 = x2993 - x3051;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3102 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3103 = x2994 - x3052;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3103 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x3104 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x3104 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x3105 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x3105 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x3106 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x3106 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3107 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x3107 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3108 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x3108 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3109 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x3109 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3110 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x3110 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3111 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x3111 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3112 = x3104 - x3111;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3113 = (x3112 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x3114 = x7 - x3113;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3114);
          reg = x3114;
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3115 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x3115 != Fp::invalid());
      if (x3115 != 0) {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3116 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x3116 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x3117 = x6 - x3116;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x3117 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3118 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x3118 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3119 = x3118 - x3104;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3120 = x3119 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3121 = Fp(x3120.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3121);
            reg = x3121;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3122 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x3122 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3123 = x3120 - x3122;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3124 = x3123 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3125 = Fp(x3124.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3125);
            reg = x3125;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3126 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x3126 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3127 = x3124 - x3126;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3128 = x3127 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3129 = Fp(x3128.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3129);
            reg = x3129;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3130 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x3130 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3131 = x3128 - x3130;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3132 = x3131 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3132);
          reg = x3132;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x3133 = x7 - x3115;
      if (x3133 != 0) {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3134 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x3134 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x3135 = x7 - x3134;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x3136 = x5 - x3134;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x3137 = x3135 * x3136;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x3137 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3138 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x3138 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x3139 = x3104 - x3138;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x3139 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3140 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x3140 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3141 = x3140 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3142 = x3141 + x3134;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3143 = x3105 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3144 = x3142 - x3143;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3145 = x3144 + x3106;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3146 = Fp(x3145.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3146);
            reg = x3146;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3147 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x3147 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3148 = x3145 - x3147;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3149 = x3148 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3150 = Fp(x3149.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3150);
            reg = x3150;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3151 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x3151 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3152 = x3149 - x3151;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3153 = x3152 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3154 = Fp(x3153.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3154);
            reg = x3154;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3155 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x3155 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3156 = x3153 - x3155;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3157 = x3156 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3157);
          reg = x3157;
        }
        if (x3136 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3158 = x3049 - x3107;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3158 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3159 = x3050 - x3108;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3159 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3160 = x3051 - x3109;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3160 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3161 = x3052 - x3110;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3161 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x3162 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x3162 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x3163 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x3163 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x3164 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x3164 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3165 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x3165 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3166 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x3166 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3167 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x3167 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3168 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x3168 != Fp::invalid());
      {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3169 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x3169 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3170 = x3162 - x3169;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3171 = (x3170 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x3172 = x7 - x3171;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3172);
          reg = x3172;
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3173 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x3173 != Fp::invalid());
      if (x3173 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3174 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x3174 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x3175 = x6 - x3174;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x3175 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3176 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x3176 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3177 = x3176 - x3162;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3178 = x3177 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3179 = Fp(x3178.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3179);
            reg = x3179;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3180 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x3180 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3181 = x3178 - x3180;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3182 = x3181 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3183 = Fp(x3182.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3183);
            reg = x3183;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3184 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x3184 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3185 = x3182 - x3184;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3186 = x3185 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3187 = Fp(x3186.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3187);
            reg = x3187;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3188 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x3188 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3189 = x3186 - x3188;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3190 = x3189 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3190);
          reg = x3190;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x3191 = x7 - x3173;
      if (x3191 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3192 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x3192 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x3193 = x7 - x3192;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x3194 = x5 - x3192;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x3195 = x3193 * x3194;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x3195 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3196 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x3196 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x3197 = x3162 - x3196;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x3197 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3198 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x3198 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3199 = x3198 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3200 = x3199 + x3192;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3201 = x3163 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3202 = x3200 - x3201;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3203 = x3202 + x3164;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3204 = Fp(x3203.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3204);
            reg = x3204;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3205 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x3205 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3206 = x3203 - x3205;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3207 = x3206 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3208 = Fp(x3207.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3208);
            reg = x3208;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3209 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x3209 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3210 = x3207 - x3209;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3211 = x3210 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3212 = Fp(x3211.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3212);
            reg = x3212;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3213 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x3213 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3214 = x3211 - x3213;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3215 = x3214 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3215);
          reg = x3215;
        }
        if (x3194 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3216 = x3107 - x3165;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3216 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3217 = x3108 - x3166;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3217 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3218 = x3109 - x3167;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3218 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3219 = x3110 - x3168;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3219 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x3220 = args[2][107 * steps + ((cycle - 0) & mask)];
    assert(x3220 != Fp::invalid());
    if (x3220 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x3221 = host_outs.at(0);
        auto x3222 = host_outs.at(1);
        auto x3223 = host_outs.at(2);
        auto x3224 = host_outs.at(3);
        auto x3225 = host_outs.at(4);
        auto x3226 = host_outs.at(5);
        auto x3227 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3221);
          reg = x3221;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3222);
          reg = x3222;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3223);
          reg = x3223;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3224);
          reg = x3224;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3225);
          reg = x3225;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][141 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3226);
          reg = x3226;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3227);
          reg = x3227;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x3228 = host_outs.at(0);
        auto x3229 = host_outs.at(1);
        auto x3230 = host_outs.at(2);
        auto x3231 = host_outs.at(3);
        auto x3232 = host_outs.at(4);
        auto x3233 = host_outs.at(5);
        auto x3234 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3228);
          reg = x3228;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3229);
          reg = x3229;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3230);
          reg = x3230;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3231);
          reg = x3231;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3232);
          reg = x3232;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3233);
          reg = x3233;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3234);
          reg = x3234;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x3235 = host_outs.at(0);
        auto x3236 = host_outs.at(1);
        auto x3237 = host_outs.at(2);
        auto x3238 = host_outs.at(3);
        auto x3239 = host_outs.at(4);
        auto x3240 = host_outs.at(5);
        auto x3241 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3235);
          reg = x3235;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3236);
          reg = x3236;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3237);
          reg = x3237;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3238);
          reg = x3238;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3239);
          reg = x3239;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3240);
          reg = x3240;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3241);
          reg = x3241;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x3242 = host_outs.at(0);
        auto x3243 = host_outs.at(1);
        auto x3244 = host_outs.at(2);
        auto x3245 = host_outs.at(3);
        auto x3246 = host_outs.at(4);
        auto x3247 = host_outs.at(5);
        auto x3248 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3242);
          reg = x3242;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3243);
          reg = x3243;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3244);
          reg = x3244;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3245);
          reg = x3245;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3246);
          reg = x3246;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3247);
          reg = x3247;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3248);
          reg = x3248;
        }
      }
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x3249 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x3249 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x3250 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x3250 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x3251 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x3251 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3252 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x3252 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3253 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x3253 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3254 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x3254 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3255 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x3255 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3256 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x3256 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3257 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x3257 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3258 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x3258 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3259 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x3259 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3260 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x3260 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3261 = x3249 - x3260;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3262 = (x3261 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x3263 = x7 - x3262;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3263);
          reg = x3263;
        }
      }
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3264 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x3264 != Fp::invalid());
      if (x3264 != 0) {
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3265 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x3265 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x3266 = x6 - x3265;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x3266 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3267 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x3267 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3268 = x3267 - x3249;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3269 = x3268 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3270 = Fp(x3269.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3270);
            reg = x3270;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3271 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x3271 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3272 = x3269 - x3271;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3273 = x3272 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3274 = Fp(x3273.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3274);
            reg = x3274;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3275 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x3275 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3276 = x3273 - x3275;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3277 = x3276 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3278 = Fp(x3277.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3278);
            reg = x3278;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3279 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x3279 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3280 = x3277 - x3279;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3281 = x3280 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3281);
          reg = x3281;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x3282 = x7 - x3264;
      if (x3282 != 0) {
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3283 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x3283 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x3284 = x7 - x3283;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x3285 = x5 - x3283;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x3286 = x3284 * x3285;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x3286 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3287 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x3287 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x3288 = x3249 - x3287;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x3288 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3289 = args[2][137 * steps + ((cycle - 0) & mask)];
        assert(x3289 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3290 = x3289 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3291 = x3290 + x3283;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3292 = x3250 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3293 = x3291 - x3292;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3294 = x3293 + x3251;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3295 = Fp(x3294.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3295);
            reg = x3295;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3296 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x3296 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3297 = x3294 - x3296;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3298 = x3297 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3299 = Fp(x3298.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3299);
            reg = x3299;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3300 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x3300 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3301 = x3298 - x3300;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3302 = x3301 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3303 = Fp(x3302.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3303);
            reg = x3303;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3304 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x3304 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3305 = x3302 - x3304;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3306 = x3305 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3306);
          reg = x3306;
        }
        if (x3285 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3307 = x3252 - x3256;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3307 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3308 = x3253 - x3257;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3308 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3309 = x3254 - x3258;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3309 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3310 = x3255 - x3259;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3310 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x3311 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x3311 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x3312 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x3312 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x3313 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x3313 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3314 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x3314 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3315 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x3315 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3316 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x3316 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3317 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x3317 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3318 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x3318 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3319 = x3311 - x3318;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3320 = (x3319 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x3321 = x7 - x3320;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3321);
          reg = x3321;
        }
      }
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3322 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x3322 != Fp::invalid());
      if (x3322 != 0) {
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3323 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x3323 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x3324 = x6 - x3323;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x3324 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3325 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x3325 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3326 = x3325 - x3311;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3327 = x3326 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3328 = Fp(x3327.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3328);
            reg = x3328;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3329 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x3329 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3330 = x3327 - x3329;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3331 = x3330 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3332 = Fp(x3331.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3332);
            reg = x3332;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3333 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x3333 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3334 = x3331 - x3333;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3335 = x3334 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3336 = Fp(x3335.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3336);
            reg = x3336;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3337 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x3337 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3338 = x3335 - x3337;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3339 = x3338 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3339);
          reg = x3339;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x3340 = x7 - x3322;
      if (x3340 != 0) {
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3341 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x3341 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x3342 = x7 - x3341;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x3343 = x5 - x3341;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x3344 = x3342 * x3343;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x3344 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3345 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x3345 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x3346 = x3311 - x3345;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x3346 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3347 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x3347 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3348 = x3347 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3349 = x3348 + x3341;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3350 = x3312 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3351 = x3349 - x3350;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3352 = x3351 + x3313;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3353 = Fp(x3352.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3353);
            reg = x3353;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3354 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x3354 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3355 = x3352 - x3354;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3356 = x3355 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3357 = Fp(x3356.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3357);
            reg = x3357;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3358 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x3358 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3359 = x3356 - x3358;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3360 = x3359 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3361 = Fp(x3360.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3361);
            reg = x3361;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3362 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x3362 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3363 = x3360 - x3362;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3364 = x3363 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3364);
          reg = x3364;
        }
        if (x3343 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3365 = x3256 - x3314;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3365 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3366 = x3257 - x3315;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3366 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3367 = x3258 - x3316;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3367 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3368 = x3259 - x3317;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3368 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x3369 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x3369 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x3370 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x3370 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x3371 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x3371 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3372 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x3372 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3373 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x3373 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3374 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x3374 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3375 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x3375 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3376 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x3376 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3377 = x3369 - x3376;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3378 = (x3377 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x3379 = x7 - x3378;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3379);
          reg = x3379;
        }
      }
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3380 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x3380 != Fp::invalid());
      if (x3380 != 0) {
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3381 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x3381 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x3382 = x6 - x3381;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x3382 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3383 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x3383 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3384 = x3383 - x3369;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3385 = x3384 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3386 = Fp(x3385.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3386);
            reg = x3386;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3387 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x3387 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3388 = x3385 - x3387;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3389 = x3388 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3390 = Fp(x3389.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3390);
            reg = x3390;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3391 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x3391 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3392 = x3389 - x3391;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3393 = x3392 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3394 = Fp(x3393.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3394);
            reg = x3394;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3395 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x3395 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3396 = x3393 - x3395;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3397 = x3396 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3397);
          reg = x3397;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x3398 = x7 - x3380;
      if (x3398 != 0) {
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3399 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x3399 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x3400 = x7 - x3399;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x3401 = x5 - x3399;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x3402 = x3400 * x3401;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x3402 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3403 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x3403 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x3404 = x3369 - x3403;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x3404 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3405 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x3405 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3406 = x3405 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3407 = x3406 + x3399;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3408 = x3370 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3409 = x3407 - x3408;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3410 = x3409 + x3371;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3411 = Fp(x3410.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3411);
            reg = x3411;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3412 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x3412 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3413 = x3410 - x3412;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3414 = x3413 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3415 = Fp(x3414.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3415);
            reg = x3415;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3416 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x3416 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3417 = x3414 - x3416;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3418 = x3417 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3419 = Fp(x3418.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3419);
            reg = x3419;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3420 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x3420 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3421 = x3418 - x3420;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3422 = x3421 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3422);
          reg = x3422;
        }
        if (x3401 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3423 = x3314 - x3372;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3423 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3424 = x3315 - x3373;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3424 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3425 = x3316 - x3374;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3425 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3426 = x3317 - x3375;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3426 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x3427 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x3427 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
      auto x3428 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x3428 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
      auto x3429 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x3429 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3430 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x3430 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3431 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x3431 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3432 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x3432 != Fp::invalid());
      // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3433 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x3433 != Fp::invalid());
      {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3434 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x3434 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3435 = x3427 - x3434;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3436 = (x3435 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x3437 = x7 - x3436;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3437);
          reg = x3437;
        }
      }
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3438 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x3438 != Fp::invalid());
      if (x3438 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3439 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x3439 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x3440 = x6 - x3439;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x3440 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3441 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x3441 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3442 = x3441 - x3427;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3443 = x3442 - x7;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3444 = Fp(x3443.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3444);
            reg = x3444;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3445 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x3445 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3446 = x3443 - x3445;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3447 = x3446 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3448 = Fp(x3447.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3448);
            reg = x3448;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3449 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x3449 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3450 = x3447 - x3449;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3451 = x3450 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3452 = Fp(x3451.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3452);
            reg = x3452;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3453 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x3453 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3454 = x3451 - x3453;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3455 = x3454 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3455);
          reg = x3455;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x3456 = x7 - x3438;
      if (x3456 != 0) {
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3457 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x3457 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x3458 = x7 - x3457;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x3459 = x5 - x3457;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x3460 = x3458 * x3459;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x3460 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3461 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x3461 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x3462 = x3427 - x3461;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x3462 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
        auto x3463 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x3463 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3464 = x3463 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3465 = x3464 + x3457;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3466 = x3428 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3467 = x3465 - x3466;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3468 = x3467 + x3429;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3469 = Fp(x3468.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3469);
            reg = x3469;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3470 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x3470 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3471 = x3468 - x3470;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3472 = x3471 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3473 = Fp(x3472.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3473);
            reg = x3473;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3474 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x3474 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3475 = x3472 - x3474;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3476 = x3475 * x3;
        {
          // loc("cirgen/components/bytes.cpp":89:21)
          auto x3477 = Fp(x3476.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":89:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3477);
            reg = x3477;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
        auto x3478 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x3478 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":90:11)
        auto x3479 = x3476 - x3478;
        // loc("cirgen/components/bytes.cpp":90:10)
        auto x3480 = x3479 * x3;
        // loc("./cirgen/components/bits.h":61:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3480);
          reg = x3480;
        }
        if (x3459 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3481 = x3372 - x3430;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3481 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3482 = x3373 - x3431;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3482 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3483 = x3374 - x3432;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3483 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3484 = x3375 - x3433;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3484 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
  }
  if (x12 != 0) {
    // loc("cirgen/components/ram.cpp":22:3)
    {
      auto& reg = args[2][17 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x1);
      reg = x1;
    }
    // loc("cirgen/components/ram.cpp":23:3)
    {
      auto& reg = args[2][18 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x0);
      reg = x0;
    }
    // loc("cirgen/components/ram.cpp":24:3)
    {
      auto& reg = args[2][19 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("cirgen/components/u32.cpp":28:5)
    {
      auto& reg = args[2][20 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("cirgen/components/u32.cpp":28:5)
    {
      auto& reg = args[2][21 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("cirgen/components/u32.cpp":28:5)
    {
      auto& reg = args[2][22 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("cirgen/components/u32.cpp":28:5)
    {
      auto& reg = args[2][23 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
    auto x3485 = args[2][2 * steps + ((cycle - 1) & mask)];
    assert(x3485 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":52:42))
    auto x3486 = args[2][3 * steps + ((cycle - 1) & mask)];
    assert(x3486 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/Reg"("cirgen/components/ram.cpp":53:42))
    auto x3487 = args[2][4 * steps + ((cycle - 1) & mask)];
    assert(x3487 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x3488 = args[2][5 * steps + ((cycle - 1) & mask)];
    assert(x3488 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x3489 = args[2][6 * steps + ((cycle - 1) & mask)];
    assert(x3489 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x3490 = args[2][7 * steps + ((cycle - 1) & mask)];
    assert(x3490 != Fp::invalid());
    // loc("Top/PlonkHeader/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x3491 = args[2][8 * steps + ((cycle - 1) & mask)];
    assert(x3491 != Fp::invalid());
    // loc("Top/Mux/5/PlonkFini/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x3492 = args[2][20 * steps + ((cycle - 0) & mask)];
    assert(x3492 != Fp::invalid());
    // loc("Top/Mux/5/PlonkFini/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x3493 = args[2][21 * steps + ((cycle - 0) & mask)];
    assert(x3493 != Fp::invalid());
    // loc("Top/Mux/5/PlonkFini/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x3494 = args[2][22 * steps + ((cycle - 0) & mask)];
    assert(x3494 != Fp::invalid());
    // loc("Top/Mux/5/PlonkFini/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x3495 = args[2][23 * steps + ((cycle - 0) & mask)];
    assert(x3495 != Fp::invalid());
    {
      // loc("Top/Mux/5/PlonkFini/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x3496 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x3496 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x3497 = x3485 - x3496;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x3498 = (x3497 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x3499 = x7 - x3498;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][24 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3499);
        reg = x3499;
      }
    }
    // loc("Top/Mux/5/PlonkFini/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x3500 = args[2][24 * steps + ((cycle - 0) & mask)];
    assert(x3500 != Fp::invalid());
    if (x3500 != 0) {
      // loc("Top/Mux/5/PlonkFini/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x3501 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x3501 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x3502 = x6 - x3501;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x3502 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/Mux/5/PlonkFini/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x3503 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x3503 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x3504 = x3503 - x3485;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x3505 = x3504 - x7;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x3506 = Fp(x3505.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][10 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3506);
          reg = x3506;
        }
      }
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x3507 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x3507 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x3508 = x3505 - x3507;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x3509 = x3508 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x3510 = Fp(x3509.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][11 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3510);
          reg = x3510;
        }
      }
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x3511 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x3511 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x3512 = x3509 - x3511;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x3513 = x3512 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x3514 = Fp(x3513.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][12 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3514);
          reg = x3514;
        }
      }
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x3515 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x3515 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x3516 = x3513 - x3515;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x3517 = x3516 * x3;
      // loc("./cirgen/components/bits.h":61:23)
      {
        auto& reg = args[2][16 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3517);
        reg = x3517;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x3518 = x7 - x3500;
    if (x3518 != 0) {
      // loc("Top/Mux/5/PlonkFini/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x3519 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x3519 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x3520 = x7 - x3519;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x3521 = x5 - x3519;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x3522 = x3520 * x3521;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x3522 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/Mux/5/PlonkFini/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x3523 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x3523 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x3524 = x3485 - x3523;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x3524 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/Mux/5/PlonkFini/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":116:61))
      auto x3525 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x3525 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x3526 = x3525 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x3527 = x3526 + x3519;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x3528 = x3486 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x3529 = x3527 - x3528;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x3530 = x3529 + x3487;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x3531 = Fp(x3530.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][10 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3531);
          reg = x3531;
        }
      }
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x3532 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x3532 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x3533 = x3530 - x3532;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x3534 = x3533 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x3535 = Fp(x3534.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][11 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3535);
          reg = x3535;
        }
      }
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x3536 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x3536 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x3537 = x3534 - x3536;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x3538 = x3537 * x3;
      {
        // loc("cirgen/components/bytes.cpp":89:21)
        auto x3539 = Fp(x3538.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":89:12)
        {
          auto& reg = args[2][12 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3539);
          reg = x3539;
        }
      }
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":90:16))
      auto x3540 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x3540 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":90:11)
      auto x3541 = x3538 - x3540;
      // loc("cirgen/components/bytes.cpp":90:10)
      auto x3542 = x3541 * x3;
      // loc("./cirgen/components/bits.h":61:23)
      {
        auto& reg = args[2][16 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3542);
        reg = x3542;
      }
      if (x3521 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x3543 = x3488 - x3492;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x3543 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x3544 = x3489 - x3493;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x3544 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x3545 = x3490 - x3494;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x3545 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x3546 = x3491 - x3495;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x3546 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
  }
  if (x8 != 0) {
    {
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3547 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x3547 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3548 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x3548 != Fp::invalid());
      host_args.at(0) = x3547;
      host_args.at(1) = x3548;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3549 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x3549 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3550 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x3550 != Fp::invalid());
      host_args.at(0) = x3549;
      host_args.at(1) = x3550;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3551 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x3551 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3552 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x3552 != Fp::invalid());
      host_args.at(0) = x3551;
      host_args.at(1) = x3552;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3553 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x3553 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3554 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x3554 != Fp::invalid());
      host_args.at(0) = x3553;
      host_args.at(1) = x3554;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3555 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x3555 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3556 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x3556 != Fp::invalid());
      host_args.at(0) = x3555;
      host_args.at(1) = x3556;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3557 = args[2][20 * steps + ((cycle - 0) & mask)];
      assert(x3557 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3558 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x3558 != Fp::invalid());
      host_args.at(0) = x3557;
      host_args.at(1) = x3558;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3559 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x3559 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3560 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x3560 != Fp::invalid());
      host_args.at(0) = x3559;
      host_args.at(1) = x3560;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3561 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x3561 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3562 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x3562 != Fp::invalid());
      host_args.at(0) = x3561;
      host_args.at(1) = x3562;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3563 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x3563 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3564 = args[2][27 * steps + ((cycle - 0) & mask)];
      assert(x3564 != Fp::invalid());
      host_args.at(0) = x3563;
      host_args.at(1) = x3564;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3565 = args[2][28 * steps + ((cycle - 0) & mask)];
      assert(x3565 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3566 = args[2][29 * steps + ((cycle - 0) & mask)];
      assert(x3566 != Fp::invalid());
      host_args.at(0) = x3565;
      host_args.at(1) = x3566;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3567 = args[2][30 * steps + ((cycle - 0) & mask)];
      assert(x3567 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3568 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x3568 != Fp::invalid());
      host_args.at(0) = x3567;
      host_args.at(1) = x3568;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3569 = args[2][32 * steps + ((cycle - 0) & mask)];
      assert(x3569 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3570 = args[2][33 * steps + ((cycle - 0) & mask)];
      assert(x3570 != Fp::invalid());
      host_args.at(0) = x3569;
      host_args.at(1) = x3570;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3571 = args[2][34 * steps + ((cycle - 0) & mask)];
      assert(x3571 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3572 = args[2][35 * steps + ((cycle - 0) & mask)];
      assert(x3572 != Fp::invalid());
      host_args.at(0) = x3571;
      host_args.at(1) = x3572;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3573 = args[2][36 * steps + ((cycle - 0) & mask)];
      assert(x3573 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3574 = args[2][37 * steps + ((cycle - 0) & mask)];
      assert(x3574 != Fp::invalid());
      host_args.at(0) = x3573;
      host_args.at(1) = x3574;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3575 = args[2][38 * steps + ((cycle - 0) & mask)];
      assert(x3575 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3576 = args[2][39 * steps + ((cycle - 0) & mask)];
      assert(x3576 != Fp::invalid());
      host_args.at(0) = x3575;
      host_args.at(1) = x3576;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3577 = args[2][40 * steps + ((cycle - 0) & mask)];
      assert(x3577 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3578 = args[2][41 * steps + ((cycle - 0) & mask)];
      assert(x3578 != Fp::invalid());
      host_args.at(0) = x3577;
      host_args.at(1) = x3578;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3579 = args[2][42 * steps + ((cycle - 0) & mask)];
      assert(x3579 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3580 = args[2][43 * steps + ((cycle - 0) & mask)];
      assert(x3580 != Fp::invalid());
      host_args.at(0) = x3579;
      host_args.at(1) = x3580;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3581 = args[2][44 * steps + ((cycle - 0) & mask)];
      assert(x3581 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3582 = args[2][45 * steps + ((cycle - 0) & mask)];
      assert(x3582 != Fp::invalid());
      host_args.at(0) = x3581;
      host_args.at(1) = x3582;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3583 = args[2][46 * steps + ((cycle - 0) & mask)];
      assert(x3583 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3584 = args[2][47 * steps + ((cycle - 0) & mask)];
      assert(x3584 != Fp::invalid());
      host_args.at(0) = x3583;
      host_args.at(1) = x3584;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3585 = args[2][48 * steps + ((cycle - 0) & mask)];
      assert(x3585 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3586 = args[2][49 * steps + ((cycle - 0) & mask)];
      assert(x3586 != Fp::invalid());
      host_args.at(0) = x3585;
      host_args.at(1) = x3586;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3587 = args[2][50 * steps + ((cycle - 0) & mask)];
      assert(x3587 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3588 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x3588 != Fp::invalid());
      host_args.at(0) = x3587;
      host_args.at(1) = x3588;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
    }
  }
  if (x9 != 0) {
    {
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3589 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x3589 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3590 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x3590 != Fp::invalid());
      host_args.at(0) = x3589;
      host_args.at(1) = x3590;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3591 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x3591 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3592 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x3592 != Fp::invalid());
      host_args.at(0) = x3591;
      host_args.at(1) = x3592;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3593 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x3593 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3594 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x3594 != Fp::invalid());
      host_args.at(0) = x3593;
      host_args.at(1) = x3594;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3595 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x3595 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3596 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x3596 != Fp::invalid());
      host_args.at(0) = x3595;
      host_args.at(1) = x3596;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3597 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x3597 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3598 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x3598 != Fp::invalid());
      host_args.at(0) = x3597;
      host_args.at(1) = x3598;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3599 = args[2][20 * steps + ((cycle - 0) & mask)];
      assert(x3599 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3600 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x3600 != Fp::invalid());
      host_args.at(0) = x3599;
      host_args.at(1) = x3600;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3601 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x3601 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3602 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x3602 != Fp::invalid());
      host_args.at(0) = x3601;
      host_args.at(1) = x3602;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3603 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x3603 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3604 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x3604 != Fp::invalid());
      host_args.at(0) = x3603;
      host_args.at(1) = x3604;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3605 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x3605 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3606 = args[2][27 * steps + ((cycle - 0) & mask)];
      assert(x3606 != Fp::invalid());
      host_args.at(0) = x3605;
      host_args.at(1) = x3606;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3607 = args[2][28 * steps + ((cycle - 0) & mask)];
      assert(x3607 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3608 = args[2][29 * steps + ((cycle - 0) & mask)];
      assert(x3608 != Fp::invalid());
      host_args.at(0) = x3607;
      host_args.at(1) = x3608;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3609 = args[2][30 * steps + ((cycle - 0) & mask)];
      assert(x3609 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3610 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x3610 != Fp::invalid());
      host_args.at(0) = x3609;
      host_args.at(1) = x3610;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3611 = args[2][32 * steps + ((cycle - 0) & mask)];
      assert(x3611 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3612 = args[2][33 * steps + ((cycle - 0) & mask)];
      assert(x3612 != Fp::invalid());
      host_args.at(0) = x3611;
      host_args.at(1) = x3612;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3613 = args[2][34 * steps + ((cycle - 0) & mask)];
      assert(x3613 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3614 = args[2][35 * steps + ((cycle - 0) & mask)];
      assert(x3614 != Fp::invalid());
      host_args.at(0) = x3613;
      host_args.at(1) = x3614;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3615 = args[2][36 * steps + ((cycle - 0) & mask)];
      assert(x3615 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3616 = args[2][37 * steps + ((cycle - 0) & mask)];
      assert(x3616 != Fp::invalid());
      host_args.at(0) = x3615;
      host_args.at(1) = x3616;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3617 = args[2][38 * steps + ((cycle - 0) & mask)];
      assert(x3617 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3618 = args[2][39 * steps + ((cycle - 0) & mask)];
      assert(x3618 != Fp::invalid());
      host_args.at(0) = x3617;
      host_args.at(1) = x3618;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3619 = args[2][40 * steps + ((cycle - 0) & mask)];
      assert(x3619 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3620 = args[2][41 * steps + ((cycle - 0) & mask)];
      assert(x3620 != Fp::invalid());
      host_args.at(0) = x3619;
      host_args.at(1) = x3620;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
    }
  }
  if (x10 != 0) {
    {
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3621 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x3621 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3622 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x3622 != Fp::invalid());
      host_args.at(0) = x3621;
      host_args.at(1) = x3622;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3623 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x3623 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3624 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x3624 != Fp::invalid());
      host_args.at(0) = x3623;
      host_args.at(1) = x3624;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3625 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x3625 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3626 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x3626 != Fp::invalid());
      host_args.at(0) = x3625;
      host_args.at(1) = x3626;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3627 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x3627 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3628 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x3628 != Fp::invalid());
      host_args.at(0) = x3627;
      host_args.at(1) = x3628;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3629 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x3629 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3630 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x3630 != Fp::invalid());
      host_args.at(0) = x3629;
      host_args.at(1) = x3630;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3631 = args[2][20 * steps + ((cycle - 0) & mask)];
      assert(x3631 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3632 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x3632 != Fp::invalid());
      host_args.at(0) = x3631;
      host_args.at(1) = x3632;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3633 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x3633 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3634 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x3634 != Fp::invalid());
      host_args.at(0) = x3633;
      host_args.at(1) = x3634;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3635 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x3635 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3636 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x3636 != Fp::invalid());
      host_args.at(0) = x3635;
      host_args.at(1) = x3636;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3637 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x3637 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3638 = args[2][27 * steps + ((cycle - 0) & mask)];
      assert(x3638 != Fp::invalid());
      host_args.at(0) = x3637;
      host_args.at(1) = x3638;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3639 = args[2][28 * steps + ((cycle - 0) & mask)];
      assert(x3639 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3640 = args[2][29 * steps + ((cycle - 0) & mask)];
      assert(x3640 != Fp::invalid());
      host_args.at(0) = x3639;
      host_args.at(1) = x3640;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3641 = args[2][30 * steps + ((cycle - 0) & mask)];
      assert(x3641 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3642 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x3642 != Fp::invalid());
      host_args.at(0) = x3641;
      host_args.at(1) = x3642;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3643 = args[2][32 * steps + ((cycle - 0) & mask)];
      assert(x3643 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3644 = args[2][33 * steps + ((cycle - 0) & mask)];
      assert(x3644 != Fp::invalid());
      host_args.at(0) = x3643;
      host_args.at(1) = x3644;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3645 = args[2][34 * steps + ((cycle - 0) & mask)];
      assert(x3645 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3646 = args[2][35 * steps + ((cycle - 0) & mask)];
      assert(x3646 != Fp::invalid());
      host_args.at(0) = x3645;
      host_args.at(1) = x3646;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3647 = args[2][36 * steps + ((cycle - 0) & mask)];
      assert(x3647 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3648 = args[2][37 * steps + ((cycle - 0) & mask)];
      assert(x3648 != Fp::invalid());
      host_args.at(0) = x3647;
      host_args.at(1) = x3648;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3649 = args[2][38 * steps + ((cycle - 0) & mask)];
      assert(x3649 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3650 = args[2][39 * steps + ((cycle - 0) & mask)];
      assert(x3650 != Fp::invalid());
      host_args.at(0) = x3649;
      host_args.at(1) = x3650;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3651 = args[2][40 * steps + ((cycle - 0) & mask)];
      assert(x3651 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3652 = args[2][41 * steps + ((cycle - 0) & mask)];
      assert(x3652 != Fp::invalid());
      host_args.at(0) = x3651;
      host_args.at(1) = x3652;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
    }
  }
  if (x11 != 0) {
    {
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3653 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x3653 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3654 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x3654 != Fp::invalid());
      host_args.at(0) = x3653;
      host_args.at(1) = x3654;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3655 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x3655 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3656 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x3656 != Fp::invalid());
      host_args.at(0) = x3655;
      host_args.at(1) = x3656;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3657 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x3657 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3658 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x3658 != Fp::invalid());
      host_args.at(0) = x3657;
      host_args.at(1) = x3658;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3659 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x3659 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3660 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x3660 != Fp::invalid());
      host_args.at(0) = x3659;
      host_args.at(1) = x3660;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3661 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x3661 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3662 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x3662 != Fp::invalid());
      host_args.at(0) = x3661;
      host_args.at(1) = x3662;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3663 = args[2][20 * steps + ((cycle - 0) & mask)];
      assert(x3663 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3664 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x3664 != Fp::invalid());
      host_args.at(0) = x3663;
      host_args.at(1) = x3664;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3665 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x3665 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3666 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x3666 != Fp::invalid());
      host_args.at(0) = x3665;
      host_args.at(1) = x3666;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3667 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x3667 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3668 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x3668 != Fp::invalid());
      host_args.at(0) = x3667;
      host_args.at(1) = x3668;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3669 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x3669 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3670 = args[2][27 * steps + ((cycle - 0) & mask)];
      assert(x3670 != Fp::invalid());
      host_args.at(0) = x3669;
      host_args.at(1) = x3670;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3671 = args[2][28 * steps + ((cycle - 0) & mask)];
      assert(x3671 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3672 = args[2][29 * steps + ((cycle - 0) & mask)];
      assert(x3672 != Fp::invalid());
      host_args.at(0) = x3671;
      host_args.at(1) = x3672;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3673 = args[2][30 * steps + ((cycle - 0) & mask)];
      assert(x3673 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3674 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x3674 != Fp::invalid());
      host_args.at(0) = x3673;
      host_args.at(1) = x3674;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3675 = args[2][32 * steps + ((cycle - 0) & mask)];
      assert(x3675 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3676 = args[2][33 * steps + ((cycle - 0) & mask)];
      assert(x3676 != Fp::invalid());
      host_args.at(0) = x3675;
      host_args.at(1) = x3676;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3677 = args[2][34 * steps + ((cycle - 0) & mask)];
      assert(x3677 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3678 = args[2][35 * steps + ((cycle - 0) & mask)];
      assert(x3678 != Fp::invalid());
      host_args.at(0) = x3677;
      host_args.at(1) = x3678;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3679 = args[2][36 * steps + ((cycle - 0) & mask)];
      assert(x3679 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3680 = args[2][37 * steps + ((cycle - 0) & mask)];
      assert(x3680 != Fp::invalid());
      host_args.at(0) = x3679;
      host_args.at(1) = x3680;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3681 = args[2][38 * steps + ((cycle - 0) & mask)];
      assert(x3681 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3682 = args[2][39 * steps + ((cycle - 0) & mask)];
      assert(x3682 != Fp::invalid());
      host_args.at(0) = x3681;
      host_args.at(1) = x3682;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3683 = args[2][40 * steps + ((cycle - 0) & mask)];
      assert(x3683 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3684 = args[2][41 * steps + ((cycle - 0) & mask)];
      assert(x3684 != Fp::invalid());
      host_args.at(0) = x3683;
      host_args.at(1) = x3684;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
    }
  }
  if (x12 != 0) {
    {
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3685 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x3685 != Fp::invalid());
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3686 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x3686 != Fp::invalid());
      host_args.at(0) = x3685;
      host_args.at(1) = x3686;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3687 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x3687 != Fp::invalid());
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
      auto x3688 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x3688 != Fp::invalid());
      host_args.at(0) = x3687;
      host_args.at(1) = x3688;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
    }
  }
  return x6;
}

} // namespace risc0::circuit::rv32im
// clang-format on
