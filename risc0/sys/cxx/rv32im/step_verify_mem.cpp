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
  // loc("cirgen/components/bytes.cpp":83:30)
  Fp x3(2005401601);
  // loc("cirgen/components/bytes.cpp":82:26)
  Fp x4(255);
  // loc("cirgen/components/bytes.cpp":37:25)
  Fp x5(2);
  // loc("cirgen/components/bytes.cpp":21:13)
  Fp x6(0);
  // loc("cirgen/circuit/rv32im/top.cpp":18:17)
  Fp x7(1);
  // loc("Top/Code/OneHot/Reg1"("./cirgen/components/mux.h":37:25))
  auto x8 = args[0][2 * steps + ((cycle - 0) & mask)];
  assert(x8 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg2"("./cirgen/components/mux.h":37:25))
  auto x9 = args[0][3 * steps + ((cycle - 0) & mask)];
  assert(x9 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg3"("./cirgen/components/mux.h":37:25))
  auto x10 = args[0][4 * steps + ((cycle - 0) & mask)];
  assert(x10 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg4"("./cirgen/components/mux.h":37:25))
  auto x11 = args[0][5 * steps + ((cycle - 0) & mask)];
  assert(x11 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg5"("./cirgen/components/mux.h":37:25))
  auto x12 = args[0][6 * steps + ((cycle - 0) & mask)];
  assert(x12 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg"("cirgen/circuit/rv32im/top.cpp":72:27))
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
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x14 = args[2][2 * steps + ((cycle - 1) & mask)];
    assert(x14 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x15 = args[2][3 * steps + ((cycle - 1) & mask)];
    assert(x15 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x16 = args[2][4 * steps + ((cycle - 1) & mask)];
    assert(x16 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x17 = args[2][5 * steps + ((cycle - 1) & mask)];
    assert(x17 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x18 = args[2][6 * steps + ((cycle - 1) & mask)];
    assert(x18 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x19 = args[2][7 * steps + ((cycle - 1) & mask)];
    assert(x19 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
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
        auto& reg = args[2][76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x21);
        reg = x21;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x22);
        reg = x22;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][78 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x23);
        reg = x23;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][79 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x24);
        reg = x24;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][80 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x25);
        reg = x25;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][81 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x26);
        reg = x26;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][82 * steps + cycle];
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
        auto& reg = args[2][83 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x28);
        reg = x28;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][84 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x29);
        reg = x29;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][85 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x30);
        reg = x30;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][86 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x31);
        reg = x31;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][87 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x32);
        reg = x32;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][88 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x33);
        reg = x33;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][89 * steps + cycle];
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
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x35);
        reg = x35;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x36);
        reg = x36;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x37);
        reg = x37;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x38);
        reg = x38;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x39);
        reg = x39;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x40);
        reg = x40;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x41);
        reg = x41;
      }
    }
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
    auto x42 = args[2][2 * steps + ((cycle - 1) & mask)];
    assert(x42 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":52:42))
    auto x43 = args[2][3 * steps + ((cycle - 1) & mask)];
    assert(x43 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":53:42))
    auto x44 = args[2][4 * steps + ((cycle - 1) & mask)];
    assert(x44 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x45 = args[2][5 * steps + ((cycle - 1) & mask)];
    assert(x45 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x46 = args[2][6 * steps + ((cycle - 1) & mask)];
    assert(x46 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x47 = args[2][7 * steps + ((cycle - 1) & mask)];
    assert(x47 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
    auto x48 = args[2][8 * steps + ((cycle - 1) & mask)];
    assert(x48 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x49 = args[2][79 * steps + ((cycle - 0) & mask)];
    assert(x49 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x50 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x50 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x51 = args[2][81 * steps + ((cycle - 0) & mask)];
    assert(x51 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
    auto x52 = args[2][82 * steps + ((cycle - 0) & mask)];
    assert(x52 != Fp::invalid());
    {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x53 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x53 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x54 = x42 - x53;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x55 = (x54 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x56 = x7 - x55;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][90 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x56);
        reg = x56;
      }
    }
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x57 = args[2][90 * steps + ((cycle - 0) & mask)];
    assert(x57 != Fp::invalid());
    if (x57 != 0) {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x58 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x58 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x59 = x6 - x58;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x59 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x60 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x60 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x61 = x60 - x42;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x62 = x61 - x7;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x63 = Fp(x62.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][10 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x63);
          reg = x63;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x64 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x64 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x65 = x62 - x64;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x66 = x65 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x67 = Fp(x66.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][11 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x67);
          reg = x67;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x68 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x68 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x69 = x66 - x68;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x70 = x69 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x71 = Fp(x70.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][12 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x71);
          reg = x71;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement1/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x72 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x72 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x73 = x70 - x72;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x74 = x73 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x74);
        reg = x74;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x75 = x7 - x57;
    if (x75 != 0) {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x76 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x76 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x77 = x7 - x76;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x78 = x5 - x76;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x79 = x77 * x78;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x79 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x80 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x80 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x81 = x42 - x80;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x81 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x82 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x82 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x83 = x82 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x84 = x83 + x76;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x85 = x43 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x86 = x84 - x85;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x87 = x86 + x44;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x88 = Fp(x87.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][10 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x88);
          reg = x88;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x89 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x89 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x90 = x87 - x89;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x91 = x90 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x92 = Fp(x91.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][11 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x92);
          reg = x92;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x93 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x93 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x94 = x91 - x93;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x95 = x94 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x96 = Fp(x95.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][12 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x96);
          reg = x96;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement1/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x97 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x97 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x98 = x95 - x97;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x99 = x98 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x99);
        reg = x99;
      }
      if (x78 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x100 = x45 - x49;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x100 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x101 = x46 - x50;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x101 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x102 = x47 - x51;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x102 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x103 = x48 - x52;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x103 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/Reg"("cirgen/components/ram.cpp":51:40))
    auto x104 = args[2][76 * steps + ((cycle - 0) & mask)];
    assert(x104 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/Reg1"("cirgen/components/ram.cpp":52:42))
    auto x105 = args[2][77 * steps + ((cycle - 0) & mask)];
    assert(x105 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/Reg2"("cirgen/components/ram.cpp":53:42))
    auto x106 = args[2][78 * steps + ((cycle - 0) & mask)];
    assert(x106 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x107 = args[2][86 * steps + ((cycle - 0) & mask)];
    assert(x107 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x108 = args[2][87 * steps + ((cycle - 0) & mask)];
    assert(x108 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x109 = args[2][88 * steps + ((cycle - 0) & mask)];
    assert(x109 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
    auto x110 = args[2][89 * steps + ((cycle - 0) & mask)];
    assert(x110 != Fp::invalid());
    {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x111 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x111 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x112 = x104 - x111;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x113 = (x112 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x114 = x7 - x113;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][91 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x114);
        reg = x114;
      }
    }
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x115 = args[2][91 * steps + ((cycle - 0) & mask)];
    assert(x115 != Fp::invalid());
    if (x115 != 0) {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x116 = args[2][85 * steps + ((cycle - 0) & mask)];
      assert(x116 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x117 = x6 - x116;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x117 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x118 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x118 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x119 = x118 - x104;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x120 = x119 - x7;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x121 = Fp(x120.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][13 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x121);
          reg = x121;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x122 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x122 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x123 = x120 - x122;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x124 = x123 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x125 = Fp(x124.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][14 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x125);
          reg = x125;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x126 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x126 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x127 = x124 - x126;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x128 = x127 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x129 = Fp(x128.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][15 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x129);
          reg = x129;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x130 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x130 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x131 = x128 - x130;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x132 = x131 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x132);
        reg = x132;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x133 = x7 - x115;
    if (x133 != 0) {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x134 = args[2][85 * steps + ((cycle - 0) & mask)];
      assert(x134 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x135 = x7 - x134;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x136 = x5 - x134;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x137 = x135 * x136;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x137 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x138 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x138 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x139 = x104 - x138;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x139 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x140 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x140 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x141 = x140 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x142 = x141 + x134;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x143 = x105 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x144 = x142 - x143;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x145 = x144 + x106;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x146 = Fp(x145.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][13 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x146);
          reg = x146;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x147 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x147 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x148 = x145 - x147;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x149 = x148 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x150 = Fp(x149.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][14 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x150);
          reg = x150;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x151 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x151 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x152 = x149 - x151;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x153 = x152 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x154 = Fp(x153.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][15 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x154);
          reg = x154;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x155 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x155 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x156 = x153 - x155;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x157 = x156 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x157);
        reg = x157;
      }
      if (x136 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x158 = x49 - x107;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x158 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x159 = x50 - x108;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x159 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x160 = x51 - x109;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x160 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x161 = x52 - x110;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x161 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/Reg"("cirgen/components/ram.cpp":51:40))
    auto x162 = args[2][83 * steps + ((cycle - 0) & mask)];
    assert(x162 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/Reg1"("cirgen/components/ram.cpp":52:42))
    auto x163 = args[2][84 * steps + ((cycle - 0) & mask)];
    assert(x163 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/Reg2"("cirgen/components/ram.cpp":53:42))
    auto x164 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x164 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x165 = args[2][5 * steps + ((cycle - 0) & mask)];
    assert(x165 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x166 = args[2][6 * steps + ((cycle - 0) & mask)];
    assert(x166 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x167 = args[2][7 * steps + ((cycle - 0) & mask)];
    assert(x167 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
    auto x168 = args[2][8 * steps + ((cycle - 0) & mask)];
    assert(x168 != Fp::invalid());
    {
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x169 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x169 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x170 = x162 - x169;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x171 = (x170 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x172 = x7 - x171;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][92 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x172);
        reg = x172;
      }
    }
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x173 = args[2][92 * steps + ((cycle - 0) & mask)];
    assert(x173 != Fp::invalid());
    if (x173 != 0) {
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x174 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x174 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x175 = x6 - x174;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x175 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x176 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x176 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x177 = x176 - x162;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x178 = x177 - x7;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x179 = Fp(x178.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][16 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x179);
          reg = x179;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x180 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x180 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x181 = x178 - x180;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x182 = x181 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x183 = Fp(x182.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][17 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x183);
          reg = x183;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x184 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x184 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x185 = x182 - x184;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x186 = x185 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x187 = Fp(x186.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][18 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x187);
          reg = x187;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x188 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x188 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x189 = x186 - x188;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x190 = x189 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x190);
        reg = x190;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x191 = x7 - x173;
    if (x191 != 0) {
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x192 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x192 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x193 = x7 - x192;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x194 = x5 - x192;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x195 = x193 * x194;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x195 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x196 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x196 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x197 = x162 - x196;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x197 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x198 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x198 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x199 = x198 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x200 = x199 + x192;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x201 = x163 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x202 = x200 - x201;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x203 = x202 + x164;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x204 = Fp(x203.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][16 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x204);
          reg = x204;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x205 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x205 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x206 = x203 - x205;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x207 = x206 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x208 = Fp(x207.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][17 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x208);
          reg = x208;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x209 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x209 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x210 = x207 - x209;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x211 = x210 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x212 = Fp(x211.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][18 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x212);
          reg = x212;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x213 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x213 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x214 = x211 - x213;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x215 = x214 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x215);
        reg = x215;
      }
      if (x194 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x216 = x107 - x165;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x216 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x217 = x108 - x166;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x217 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x218 = x109 - x167;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x218 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x219 = x110 - x168;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x219 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
  }
  if (x10 != 0) {
    {
      host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
      auto x220 = host_outs.at(0);
      auto x221 = host_outs.at(1);
      auto x222 = host_outs.at(2);
      auto x223 = host_outs.at(3);
      auto x224 = host_outs.at(4);
      auto x225 = host_outs.at(5);
      auto x226 = host_outs.at(6);
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][150 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x220);
        reg = x220;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][151 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x221);
        reg = x221;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][152 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x222);
        reg = x222;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][153 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x223);
        reg = x223;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][154 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x224);
        reg = x224;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][155 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x225);
        reg = x225;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][156 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x226);
        reg = x226;
      }
      host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
      auto x227 = host_outs.at(0);
      auto x228 = host_outs.at(1);
      auto x229 = host_outs.at(2);
      auto x230 = host_outs.at(3);
      auto x231 = host_outs.at(4);
      auto x232 = host_outs.at(5);
      auto x233 = host_outs.at(6);
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][157 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x227);
        reg = x227;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][158 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x228);
        reg = x228;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][159 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x229);
        reg = x229;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][160 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x230);
        reg = x230;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][161 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x231);
        reg = x231;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][162 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x232);
        reg = x232;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][163 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x233);
        reg = x233;
      }
      host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
      auto x234 = host_outs.at(0);
      auto x235 = host_outs.at(1);
      auto x236 = host_outs.at(2);
      auto x237 = host_outs.at(3);
      auto x238 = host_outs.at(4);
      auto x239 = host_outs.at(5);
      auto x240 = host_outs.at(6);
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][164 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x234);
        reg = x234;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][165 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x235);
        reg = x235;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][166 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x236);
        reg = x236;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][167 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x237);
        reg = x237;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][168 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x238);
        reg = x238;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][169 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x239);
        reg = x239;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][170 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x240);
        reg = x240;
      }
      host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
      auto x241 = host_outs.at(0);
      auto x242 = host_outs.at(1);
      auto x243 = host_outs.at(2);
      auto x244 = host_outs.at(3);
      auto x245 = host_outs.at(4);
      auto x246 = host_outs.at(5);
      auto x247 = host_outs.at(6);
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][171 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x241);
        reg = x241;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][172 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x242);
        reg = x242;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][173 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x243);
        reg = x243;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][174 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x244);
        reg = x244;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][175 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x245);
        reg = x245;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][176 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x246);
        reg = x246;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][177 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x247);
        reg = x247;
      }
      host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
      auto x248 = host_outs.at(0);
      auto x249 = host_outs.at(1);
      auto x250 = host_outs.at(2);
      auto x251 = host_outs.at(3);
      auto x252 = host_outs.at(4);
      auto x253 = host_outs.at(5);
      auto x254 = host_outs.at(6);
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][178 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x248);
        reg = x248;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][179 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x249);
        reg = x249;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][180 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x250);
        reg = x250;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][181 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x251);
        reg = x251;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][182 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x252);
        reg = x252;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][183 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x253);
        reg = x253;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][184 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x254);
        reg = x254;
      }
      host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
      auto x255 = host_outs.at(0);
      auto x256 = host_outs.at(1);
      auto x257 = host_outs.at(2);
      auto x258 = host_outs.at(3);
      auto x259 = host_outs.at(4);
      auto x260 = host_outs.at(5);
      auto x261 = host_outs.at(6);
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][185 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x255);
        reg = x255;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][186 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x256);
        reg = x256;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][187 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x257);
        reg = x257;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][188 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x258);
        reg = x258;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][189 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x259);
        reg = x259;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][190 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x260);
        reg = x260;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][191 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x261);
        reg = x261;
      }
      host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
      auto x262 = host_outs.at(0);
      auto x263 = host_outs.at(1);
      auto x264 = host_outs.at(2);
      auto x265 = host_outs.at(3);
      auto x266 = host_outs.at(4);
      auto x267 = host_outs.at(5);
      auto x268 = host_outs.at(6);
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][192 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x262);
        reg = x262;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][193 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x263);
        reg = x263;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][194 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x264);
        reg = x264;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][195 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x265);
        reg = x265;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][196 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x266);
        reg = x266;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][197 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x267);
        reg = x267;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][198 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x268);
        reg = x268;
      }
      host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
      auto x269 = host_outs.at(0);
      auto x270 = host_outs.at(1);
      auto x271 = host_outs.at(2);
      auto x272 = host_outs.at(3);
      auto x273 = host_outs.at(4);
      auto x274 = host_outs.at(5);
      auto x275 = host_outs.at(6);
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x269);
        reg = x269;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x270);
        reg = x270;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x271);
        reg = x271;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x272);
        reg = x272;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x273);
        reg = x273;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x274);
        reg = x274;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x275);
        reg = x275;
      }
    }
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
    auto x276 = args[2][2 * steps + ((cycle - 1) & mask)];
    assert(x276 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":52:42))
    auto x277 = args[2][3 * steps + ((cycle - 1) & mask)];
    assert(x277 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":53:42))
    auto x278 = args[2][4 * steps + ((cycle - 1) & mask)];
    assert(x278 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x279 = args[2][5 * steps + ((cycle - 1) & mask)];
    assert(x279 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x280 = args[2][6 * steps + ((cycle - 1) & mask)];
    assert(x280 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x281 = args[2][7 * steps + ((cycle - 1) & mask)];
    assert(x281 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
    auto x282 = args[2][8 * steps + ((cycle - 1) & mask)];
    assert(x282 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x283 = args[2][153 * steps + ((cycle - 0) & mask)];
    assert(x283 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x284 = args[2][154 * steps + ((cycle - 0) & mask)];
    assert(x284 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x285 = args[2][155 * steps + ((cycle - 0) & mask)];
    assert(x285 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
    auto x286 = args[2][156 * steps + ((cycle - 0) & mask)];
    assert(x286 != Fp::invalid());
    {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x287 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x287 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x288 = x276 - x287;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x289 = (x288 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x290 = x7 - x289;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][199 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x290);
        reg = x290;
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x291 = args[2][199 * steps + ((cycle - 0) & mask)];
    assert(x291 != Fp::invalid());
    if (x291 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x292 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x292 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x293 = x6 - x292;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x293 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x294 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x294 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x295 = x294 - x276;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x296 = x295 - x7;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x297 = Fp(x296.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][13 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x297);
          reg = x297;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x298 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x298 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x299 = x296 - x298;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x300 = x299 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x301 = Fp(x300.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][14 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x301);
          reg = x301;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x302 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x302 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x303 = x300 - x302;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x304 = x303 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x305 = Fp(x304.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][15 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x305);
          reg = x305;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x306 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x306 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x307 = x304 - x306;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x308 = x307 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x308);
        reg = x308;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x309 = x7 - x291;
    if (x309 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x310 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x310 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x311 = x7 - x310;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x312 = x5 - x310;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x313 = x311 * x312;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x313 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x314 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x314 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x315 = x276 - x314;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x315 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x316 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x316 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x317 = x316 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x318 = x317 + x310;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x319 = x277 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x320 = x318 - x319;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x321 = x320 + x278;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x322 = Fp(x321.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][13 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x322);
          reg = x322;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x323 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x323 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x324 = x321 - x323;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x325 = x324 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x326 = Fp(x325.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][14 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x326);
          reg = x326;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x327 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x327 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x328 = x325 - x327;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x329 = x328 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x330 = Fp(x329.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][15 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x330);
          reg = x330;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x331 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x331 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x332 = x329 - x331;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x333 = x332 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x333);
        reg = x333;
      }
      if (x312 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x334 = x279 - x283;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x334 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x335 = x280 - x284;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x335 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x336 = x281 - x285;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x336 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x337 = x282 - x286;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x337 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg"("cirgen/components/ram.cpp":51:40))
    auto x338 = args[2][150 * steps + ((cycle - 0) & mask)];
    assert(x338 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg1"("cirgen/components/ram.cpp":52:42))
    auto x339 = args[2][151 * steps + ((cycle - 0) & mask)];
    assert(x339 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg2"("cirgen/components/ram.cpp":53:42))
    auto x340 = args[2][152 * steps + ((cycle - 0) & mask)];
    assert(x340 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement9/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x341 = args[2][160 * steps + ((cycle - 0) & mask)];
    assert(x341 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement9/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x342 = args[2][161 * steps + ((cycle - 0) & mask)];
    assert(x342 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement9/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x343 = args[2][162 * steps + ((cycle - 0) & mask)];
    assert(x343 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement9/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
    auto x344 = args[2][163 * steps + ((cycle - 0) & mask)];
    assert(x344 != Fp::invalid());
    {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement9/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x345 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x345 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x346 = x338 - x345;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x347 = (x346 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x348 = x7 - x347;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][200 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x348);
        reg = x348;
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x349 = args[2][200 * steps + ((cycle - 0) & mask)];
    assert(x349 != Fp::invalid());
    if (x349 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement9/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x350 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x350 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x351 = x6 - x350;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x351 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement9/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x352 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x352 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x353 = x352 - x338;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x354 = x353 - x7;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x355 = Fp(x354.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][16 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x355);
          reg = x355;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x356 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x356 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x357 = x354 - x356;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x358 = x357 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x359 = Fp(x358.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][17 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x359);
          reg = x359;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x360 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x360 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x361 = x358 - x360;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x362 = x361 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x363 = Fp(x362.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][18 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x363);
          reg = x363;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x364 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x364 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x365 = x362 - x364;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x366 = x365 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x366);
        reg = x366;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x367 = x7 - x349;
    if (x367 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement9/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x368 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x368 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x369 = x7 - x368;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x370 = x5 - x368;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x371 = x369 * x370;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x371 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement9/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x372 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x372 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x373 = x338 - x372;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x373 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement9/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x374 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x374 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x375 = x374 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x376 = x375 + x368;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x377 = x339 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x378 = x376 - x377;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x379 = x378 + x340;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x380 = Fp(x379.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][16 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x380);
          reg = x380;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x381 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x381 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x382 = x379 - x381;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x383 = x382 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x384 = Fp(x383.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][17 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x384);
          reg = x384;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x385 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x385 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x386 = x383 - x385;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x387 = x386 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x388 = Fp(x387.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][18 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x388);
          reg = x388;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x389 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x389 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x390 = x387 - x389;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x391 = x390 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x391);
        reg = x391;
      }
      if (x370 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x392 = x283 - x341;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x392 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x393 = x284 - x342;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x393 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x394 = x285 - x343;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x394 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x395 = x286 - x344;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x395 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement9/Reg"("cirgen/components/ram.cpp":51:40))
    auto x396 = args[2][157 * steps + ((cycle - 0) & mask)];
    assert(x396 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement9/Reg1"("cirgen/components/ram.cpp":52:42))
    auto x397 = args[2][158 * steps + ((cycle - 0) & mask)];
    assert(x397 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement9/Reg2"("cirgen/components/ram.cpp":53:42))
    auto x398 = args[2][159 * steps + ((cycle - 0) & mask)];
    assert(x398 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement10/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x399 = args[2][167 * steps + ((cycle - 0) & mask)];
    assert(x399 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement10/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x400 = args[2][168 * steps + ((cycle - 0) & mask)];
    assert(x400 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement10/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x401 = args[2][169 * steps + ((cycle - 0) & mask)];
    assert(x401 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement10/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
    auto x402 = args[2][170 * steps + ((cycle - 0) & mask)];
    assert(x402 != Fp::invalid());
    {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement10/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x403 = args[2][164 * steps + ((cycle - 0) & mask)];
      assert(x403 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x404 = x396 - x403;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x405 = (x404 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x406 = x7 - x405;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][201 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x406);
        reg = x406;
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x407 = args[2][201 * steps + ((cycle - 0) & mask)];
    assert(x407 != Fp::invalid());
    if (x407 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement10/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x408 = args[2][166 * steps + ((cycle - 0) & mask)];
      assert(x408 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x409 = x6 - x408;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x409 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement10/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x410 = args[2][164 * steps + ((cycle - 0) & mask)];
      assert(x410 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x411 = x410 - x396;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x412 = x411 - x7;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x413 = Fp(x412.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][19 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x413);
          reg = x413;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x414 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x414 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x415 = x412 - x414;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x416 = x415 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x417 = Fp(x416.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][20 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x417);
          reg = x417;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x418 = args[2][20 * steps + ((cycle - 0) & mask)];
      assert(x418 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x419 = x416 - x418;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x420 = x419 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x421 = Fp(x420.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x421);
          reg = x421;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x422 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x422 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x423 = x420 - x422;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x424 = x423 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x424);
        reg = x424;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x425 = x7 - x407;
    if (x425 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement10/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x426 = args[2][166 * steps + ((cycle - 0) & mask)];
      assert(x426 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x427 = x7 - x426;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x428 = x5 - x426;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x429 = x427 * x428;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x429 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement10/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x430 = args[2][164 * steps + ((cycle - 0) & mask)];
      assert(x430 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x431 = x396 - x430;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x431 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement10/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x432 = args[2][165 * steps + ((cycle - 0) & mask)];
      assert(x432 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x433 = x432 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x434 = x433 + x426;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x435 = x397 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x436 = x434 - x435;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x437 = x436 + x398;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x438 = Fp(x437.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][19 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x438);
          reg = x438;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x439 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x439 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x440 = x437 - x439;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x441 = x440 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x442 = Fp(x441.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][20 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x442);
          reg = x442;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x443 = args[2][20 * steps + ((cycle - 0) & mask)];
      assert(x443 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x444 = x441 - x443;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x445 = x444 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x446 = Fp(x445.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x446);
          reg = x446;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x447 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x447 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x448 = x445 - x447;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x449 = x448 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x449);
        reg = x449;
      }
      if (x428 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x450 = x341 - x399;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x450 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x451 = x342 - x400;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x451 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x452 = x343 - x401;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x452 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x453 = x344 - x402;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x453 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement10/Reg"("cirgen/components/ram.cpp":51:40))
    auto x454 = args[2][164 * steps + ((cycle - 0) & mask)];
    assert(x454 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement10/Reg1"("cirgen/components/ram.cpp":52:42))
    auto x455 = args[2][165 * steps + ((cycle - 0) & mask)];
    assert(x455 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement10/Reg2"("cirgen/components/ram.cpp":53:42))
    auto x456 = args[2][166 * steps + ((cycle - 0) & mask)];
    assert(x456 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement11/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x457 = args[2][174 * steps + ((cycle - 0) & mask)];
    assert(x457 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement11/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x458 = args[2][175 * steps + ((cycle - 0) & mask)];
    assert(x458 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement11/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x459 = args[2][176 * steps + ((cycle - 0) & mask)];
    assert(x459 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement11/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
    auto x460 = args[2][177 * steps + ((cycle - 0) & mask)];
    assert(x460 != Fp::invalid());
    {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement11/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x461 = args[2][171 * steps + ((cycle - 0) & mask)];
      assert(x461 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x462 = x454 - x461;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x463 = (x462 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x464 = x7 - x463;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][202 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x464);
        reg = x464;
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkVerifier3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x465 = args[2][202 * steps + ((cycle - 0) & mask)];
    assert(x465 != Fp::invalid());
    if (x465 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement11/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x466 = args[2][173 * steps + ((cycle - 0) & mask)];
      assert(x466 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x467 = x6 - x466;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x467 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement11/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x468 = args[2][171 * steps + ((cycle - 0) & mask)];
      assert(x468 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x469 = x468 - x454;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x470 = x469 - x7;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x471 = Fp(x470.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x471);
          reg = x471;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x472 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x472 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x473 = x470 - x472;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x474 = x473 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x475 = Fp(x474.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x475);
          reg = x475;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x476 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x476 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x477 = x474 - x476;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x478 = x477 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x479 = Fp(x478.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x479);
          reg = x479;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x480 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x480 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x481 = x478 - x480;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x482 = x481 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x482);
        reg = x482;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x483 = x7 - x465;
    if (x483 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement11/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x484 = args[2][173 * steps + ((cycle - 0) & mask)];
      assert(x484 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x485 = x7 - x484;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x486 = x5 - x484;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x487 = x485 * x486;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x487 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement11/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x488 = args[2][171 * steps + ((cycle - 0) & mask)];
      assert(x488 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x489 = x454 - x488;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x489 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement11/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x490 = args[2][172 * steps + ((cycle - 0) & mask)];
      assert(x490 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x491 = x490 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x492 = x491 + x484;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x493 = x455 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x494 = x492 - x493;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x495 = x494 + x456;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x496 = Fp(x495.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x496);
          reg = x496;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x497 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x497 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x498 = x495 - x497;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x499 = x498 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x500 = Fp(x499.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x500);
          reg = x500;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x501 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x501 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x502 = x499 - x501;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x503 = x502 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x504 = Fp(x503.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x504);
          reg = x504;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x505 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x505 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x506 = x503 - x505;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x507 = x506 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x507);
        reg = x507;
      }
      if (x486 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x508 = x399 - x457;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x508 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x509 = x400 - x458;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x509 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x510 = x401 - x459;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x510 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x511 = x402 - x460;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x511 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement11/Reg"("cirgen/components/ram.cpp":51:40))
    auto x512 = args[2][171 * steps + ((cycle - 0) & mask)];
    assert(x512 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement11/Reg1"("cirgen/components/ram.cpp":52:42))
    auto x513 = args[2][172 * steps + ((cycle - 0) & mask)];
    assert(x513 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement11/Reg2"("cirgen/components/ram.cpp":53:42))
    auto x514 = args[2][173 * steps + ((cycle - 0) & mask)];
    assert(x514 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement12/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x515 = args[2][181 * steps + ((cycle - 0) & mask)];
    assert(x515 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement12/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x516 = args[2][182 * steps + ((cycle - 0) & mask)];
    assert(x516 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement12/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x517 = args[2][183 * steps + ((cycle - 0) & mask)];
    assert(x517 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement12/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
    auto x518 = args[2][184 * steps + ((cycle - 0) & mask)];
    assert(x518 != Fp::invalid());
    {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement12/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x519 = args[2][178 * steps + ((cycle - 0) & mask)];
      assert(x519 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x520 = x512 - x519;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x521 = (x520 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x522 = x7 - x521;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][203 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x522);
        reg = x522;
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkVerifier4/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x523 = args[2][203 * steps + ((cycle - 0) & mask)];
    assert(x523 != Fp::invalid());
    if (x523 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement12/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x524 = args[2][180 * steps + ((cycle - 0) & mask)];
      assert(x524 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x525 = x6 - x524;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x525 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement12/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x526 = args[2][178 * steps + ((cycle - 0) & mask)];
      assert(x526 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x527 = x526 - x512;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x528 = x527 - x7;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x529 = Fp(x528.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][25 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x529);
          reg = x529;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x530 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x530 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x531 = x528 - x530;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x532 = x531 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x533 = Fp(x532.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][26 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x533);
          reg = x533;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x534 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x534 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x535 = x532 - x534;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x536 = x535 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x537 = Fp(x536.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][27 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x537);
          reg = x537;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x538 = args[2][27 * steps + ((cycle - 0) & mask)];
      assert(x538 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x539 = x536 - x538;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x540 = x539 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][78 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x540);
        reg = x540;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x541 = x7 - x523;
    if (x541 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement12/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x542 = args[2][180 * steps + ((cycle - 0) & mask)];
      assert(x542 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x543 = x7 - x542;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x544 = x5 - x542;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x545 = x543 * x544;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x545 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement12/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x546 = args[2][178 * steps + ((cycle - 0) & mask)];
      assert(x546 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x547 = x512 - x546;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x547 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement12/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x548 = args[2][179 * steps + ((cycle - 0) & mask)];
      assert(x548 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x549 = x548 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x550 = x549 + x542;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x551 = x513 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x552 = x550 - x551;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x553 = x552 + x514;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x554 = Fp(x553.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][25 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x554);
          reg = x554;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x555 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x555 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x556 = x553 - x555;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x557 = x556 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x558 = Fp(x557.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][26 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x558);
          reg = x558;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x559 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x559 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x560 = x557 - x559;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x561 = x560 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x562 = Fp(x561.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][27 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x562);
          reg = x562;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x563 = args[2][27 * steps + ((cycle - 0) & mask)];
      assert(x563 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x564 = x561 - x563;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x565 = x564 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][78 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x565);
        reg = x565;
      }
      if (x544 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x566 = x457 - x515;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x566 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x567 = x458 - x516;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x567 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x568 = x459 - x517;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x568 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x569 = x460 - x518;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x569 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement12/Reg"("cirgen/components/ram.cpp":51:40))
    auto x570 = args[2][178 * steps + ((cycle - 0) & mask)];
    assert(x570 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement12/Reg1"("cirgen/components/ram.cpp":52:42))
    auto x571 = args[2][179 * steps + ((cycle - 0) & mask)];
    assert(x571 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement12/Reg2"("cirgen/components/ram.cpp":53:42))
    auto x572 = args[2][180 * steps + ((cycle - 0) & mask)];
    assert(x572 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement13/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x573 = args[2][188 * steps + ((cycle - 0) & mask)];
    assert(x573 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement13/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x574 = args[2][189 * steps + ((cycle - 0) & mask)];
    assert(x574 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement13/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x575 = args[2][190 * steps + ((cycle - 0) & mask)];
    assert(x575 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement13/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
    auto x576 = args[2][191 * steps + ((cycle - 0) & mask)];
    assert(x576 != Fp::invalid());
    {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement13/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x577 = args[2][185 * steps + ((cycle - 0) & mask)];
      assert(x577 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x578 = x570 - x577;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x579 = (x578 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x580 = x7 - x579;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][204 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x580);
        reg = x580;
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkVerifier5/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x581 = args[2][204 * steps + ((cycle - 0) & mask)];
    assert(x581 != Fp::invalid());
    if (x581 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement13/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x582 = args[2][187 * steps + ((cycle - 0) & mask)];
      assert(x582 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x583 = x6 - x582;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x583 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement13/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x584 = args[2][185 * steps + ((cycle - 0) & mask)];
      assert(x584 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x585 = x584 - x570;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x586 = x585 - x7;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x587 = Fp(x586.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][28 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x587);
          reg = x587;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement9/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x588 = args[2][28 * steps + ((cycle - 0) & mask)];
      assert(x588 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x589 = x586 - x588;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x590 = x589 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x591 = Fp(x590.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][29 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x591);
          reg = x591;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement9/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x592 = args[2][29 * steps + ((cycle - 0) & mask)];
      assert(x592 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x593 = x590 - x592;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x594 = x593 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x595 = Fp(x594.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][30 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x595);
          reg = x595;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement10/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x596 = args[2][30 * steps + ((cycle - 0) & mask)];
      assert(x596 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x597 = x594 - x596;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x598 = x597 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][79 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x598);
        reg = x598;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x599 = x7 - x581;
    if (x599 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement13/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x600 = args[2][187 * steps + ((cycle - 0) & mask)];
      assert(x600 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x601 = x7 - x600;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x602 = x5 - x600;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x603 = x601 * x602;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x603 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement13/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x604 = args[2][185 * steps + ((cycle - 0) & mask)];
      assert(x604 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x605 = x570 - x604;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x605 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement13/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x606 = args[2][186 * steps + ((cycle - 0) & mask)];
      assert(x606 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x607 = x606 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x608 = x607 + x600;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x609 = x571 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x610 = x608 - x609;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x611 = x610 + x572;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x612 = Fp(x611.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][28 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x612);
          reg = x612;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement9/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x613 = args[2][28 * steps + ((cycle - 0) & mask)];
      assert(x613 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x614 = x611 - x613;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x615 = x614 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x616 = Fp(x615.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][29 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x616);
          reg = x616;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement9/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x617 = args[2][29 * steps + ((cycle - 0) & mask)];
      assert(x617 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x618 = x615 - x617;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x619 = x618 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x620 = Fp(x619.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][30 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x620);
          reg = x620;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement10/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x621 = args[2][30 * steps + ((cycle - 0) & mask)];
      assert(x621 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x622 = x619 - x621;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x623 = x622 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][79 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x623);
        reg = x623;
      }
      if (x602 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x624 = x515 - x573;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x624 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x625 = x516 - x574;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x625 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x626 = x517 - x575;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x626 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x627 = x518 - x576;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x627 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement13/Reg"("cirgen/components/ram.cpp":51:40))
    auto x628 = args[2][185 * steps + ((cycle - 0) & mask)];
    assert(x628 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement13/Reg1"("cirgen/components/ram.cpp":52:42))
    auto x629 = args[2][186 * steps + ((cycle - 0) & mask)];
    assert(x629 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement13/Reg2"("cirgen/components/ram.cpp":53:42))
    auto x630 = args[2][187 * steps + ((cycle - 0) & mask)];
    assert(x630 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement14/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x631 = args[2][195 * steps + ((cycle - 0) & mask)];
    assert(x631 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement14/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x632 = args[2][196 * steps + ((cycle - 0) & mask)];
    assert(x632 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement14/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x633 = args[2][197 * steps + ((cycle - 0) & mask)];
    assert(x633 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement14/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
    auto x634 = args[2][198 * steps + ((cycle - 0) & mask)];
    assert(x634 != Fp::invalid());
    {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement14/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x635 = args[2][192 * steps + ((cycle - 0) & mask)];
      assert(x635 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x636 = x628 - x635;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x637 = (x636 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x638 = x7 - x637;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][205 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x638);
        reg = x638;
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkVerifier6/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x639 = args[2][205 * steps + ((cycle - 0) & mask)];
    assert(x639 != Fp::invalid());
    if (x639 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement14/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x640 = args[2][194 * steps + ((cycle - 0) & mask)];
      assert(x640 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x641 = x6 - x640;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x641 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement14/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x642 = args[2][192 * steps + ((cycle - 0) & mask)];
      assert(x642 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x643 = x642 - x628;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x644 = x643 - x7;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x645 = Fp(x644.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][31 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x645);
          reg = x645;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement10/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x646 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x646 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x647 = x644 - x646;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x648 = x647 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x649 = Fp(x648.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][32 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x649);
          reg = x649;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement11/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x650 = args[2][32 * steps + ((cycle - 0) & mask)];
      assert(x650 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x651 = x648 - x650;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x652 = x651 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x653 = Fp(x652.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][33 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x653);
          reg = x653;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement11/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x654 = args[2][33 * steps + ((cycle - 0) & mask)];
      assert(x654 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x655 = x652 - x654;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x656 = x655 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][80 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x656);
        reg = x656;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x657 = x7 - x639;
    if (x657 != 0) {
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement14/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x658 = args[2][194 * steps + ((cycle - 0) & mask)];
      assert(x658 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x659 = x7 - x658;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x660 = x5 - x658;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x661 = x659 * x660;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x661 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement14/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x662 = args[2][192 * steps + ((cycle - 0) & mask)];
      assert(x662 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x663 = x628 - x662;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x663 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement14/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x664 = args[2][193 * steps + ((cycle - 0) & mask)];
      assert(x664 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x665 = x664 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x666 = x665 + x658;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x667 = x629 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x668 = x666 - x667;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x669 = x668 + x630;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x670 = Fp(x669.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][31 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x670);
          reg = x670;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement10/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x671 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x671 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x672 = x669 - x671;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x673 = x672 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x674 = Fp(x673.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][32 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x674);
          reg = x674;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement11/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x675 = args[2][32 * steps + ((cycle - 0) & mask)];
      assert(x675 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x676 = x673 - x675;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x677 = x676 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x678 = Fp(x677.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][33 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x678);
          reg = x678;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement11/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x679 = args[2][33 * steps + ((cycle - 0) & mask)];
      assert(x679 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x680 = x677 - x679;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x681 = x680 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][80 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x681);
        reg = x681;
      }
      if (x660 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x682 = x573 - x631;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x682 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x683 = x574 - x632;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x683 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x684 = x575 - x633;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x684 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x685 = x576 - x634;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x685 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement14/Reg"("cirgen/components/ram.cpp":51:40))
    auto x686 = args[2][192 * steps + ((cycle - 0) & mask)];
    assert(x686 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement14/Reg1"("cirgen/components/ram.cpp":52:42))
    auto x687 = args[2][193 * steps + ((cycle - 0) & mask)];
    assert(x687 != Fp::invalid());
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkElement14/Reg2"("cirgen/components/ram.cpp":53:42))
    auto x688 = args[2][194 * steps + ((cycle - 0) & mask)];
    assert(x688 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x689 = args[2][5 * steps + ((cycle - 0) & mask)];
    assert(x689 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x690 = args[2][6 * steps + ((cycle - 0) & mask)];
    assert(x690 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x691 = args[2][7 * steps + ((cycle - 0) & mask)];
    assert(x691 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
    auto x692 = args[2][8 * steps + ((cycle - 0) & mask)];
    assert(x692 != Fp::invalid());
    {
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x693 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x693 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x694 = x686 - x693;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x695 = (x694 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x696 = x7 - x695;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][206 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x696);
        reg = x696;
      }
    }
    // loc("Top/Mux/3/RamBody/PlonkBody/RamPlonkVerifier7/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x697 = args[2][206 * steps + ((cycle - 0) & mask)];
    assert(x697 != Fp::invalid());
    if (x697 != 0) {
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x698 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x698 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x699 = x6 - x698;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x699 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x700 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x700 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x701 = x700 - x686;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x702 = x701 - x7;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x703 = Fp(x702.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][34 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x703);
          reg = x703;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement12/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x704 = args[2][34 * steps + ((cycle - 0) & mask)];
      assert(x704 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x705 = x702 - x704;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x706 = x705 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x707 = Fp(x706.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][35 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x707);
          reg = x707;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement12/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x708 = args[2][35 * steps + ((cycle - 0) & mask)];
      assert(x708 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x709 = x706 - x708;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x710 = x709 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x711 = Fp(x710.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][36 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x711);
          reg = x711;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement13/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x712 = args[2][36 * steps + ((cycle - 0) & mask)];
      assert(x712 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x713 = x710 - x712;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x714 = x713 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][81 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x714);
        reg = x714;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x715 = x7 - x697;
    if (x715 != 0) {
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x716 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x716 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x717 = x7 - x716;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x718 = x5 - x716;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x719 = x717 * x718;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x719 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x720 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x720 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x721 = x686 - x720;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x721 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x722 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x722 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x723 = x722 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x724 = x723 + x716;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x725 = x687 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x726 = x724 - x725;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x727 = x726 + x688;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x728 = Fp(x727.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][34 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x728);
          reg = x728;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement12/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x729 = args[2][34 * steps + ((cycle - 0) & mask)];
      assert(x729 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x730 = x727 - x729;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x731 = x730 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x732 = Fp(x731.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][35 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x732);
          reg = x732;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement12/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x733 = args[2][35 * steps + ((cycle - 0) & mask)];
      assert(x733 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x734 = x731 - x733;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x735 = x734 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x736 = Fp(x735.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][36 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x736);
          reg = x736;
        }
      }
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement13/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x737 = args[2][36 * steps + ((cycle - 0) & mask)];
      assert(x737 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x738 = x735 - x737;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x739 = x738 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][81 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x739);
        reg = x739;
      }
      if (x718 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x740 = x631 - x689;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x740 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x741 = x632 - x690;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x741 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x742 = x633 - x691;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x742 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x743 = x634 - x692;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x743 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
  }
  if (x11 != 0) {
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x744 = args[2][94 * steps + ((cycle - 0) & mask)];
    assert(x744 != Fp::invalid());
    if (x744 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x745 = host_outs.at(0);
        auto x746 = host_outs.at(1);
        auto x747 = host_outs.at(2);
        auto x748 = host_outs.at(3);
        auto x749 = host_outs.at(4);
        auto x750 = host_outs.at(5);
        auto x751 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x745);
          reg = x745;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x746);
          reg = x746;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x747);
          reg = x747;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x748);
          reg = x748;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x749);
          reg = x749;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][141 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x750);
          reg = x750;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x751);
          reg = x751;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x752 = host_outs.at(0);
        auto x753 = host_outs.at(1);
        auto x754 = host_outs.at(2);
        auto x755 = host_outs.at(3);
        auto x756 = host_outs.at(4);
        auto x757 = host_outs.at(5);
        auto x758 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x752);
          reg = x752;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x753);
          reg = x753;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x754);
          reg = x754;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x755);
          reg = x755;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x756);
          reg = x756;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x757);
          reg = x757;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x758);
          reg = x758;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x759 = host_outs.at(0);
        auto x760 = host_outs.at(1);
        auto x761 = host_outs.at(2);
        auto x762 = host_outs.at(3);
        auto x763 = host_outs.at(4);
        auto x764 = host_outs.at(5);
        auto x765 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x759);
          reg = x759;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x760);
          reg = x760;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x761);
          reg = x761;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x762);
          reg = x762;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x763);
          reg = x763;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x764);
          reg = x764;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x765);
          reg = x765;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x766 = host_outs.at(0);
        auto x767 = host_outs.at(1);
        auto x768 = host_outs.at(2);
        auto x769 = host_outs.at(3);
        auto x770 = host_outs.at(4);
        auto x771 = host_outs.at(5);
        auto x772 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x766);
          reg = x766;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x767);
          reg = x767;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x768);
          reg = x768;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x769);
          reg = x769;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x770);
          reg = x770;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x771);
          reg = x771;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x772);
          reg = x772;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x773 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x773 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x774 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x774 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x775 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x775 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x776 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x776 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x777 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x777 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x778 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x778 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x779 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x779 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x780 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x780 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x781 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x781 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x782 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x782 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x783 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x783 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x784 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x784 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x785 = x773 - x784;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x786 = (x785 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x787 = x7 - x786;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x787);
          reg = x787;
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x788 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x788 != Fp::invalid());
      if (x788 != 0) {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x789 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x789 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x790 = x6 - x789;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x790 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x791 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x791 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x792 = x791 - x773;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x793 = x792 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x794 = Fp(x793.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x794);
            reg = x794;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x795 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x795 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x796 = x793 - x795;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x797 = x796 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x798 = Fp(x797.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x798);
            reg = x798;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x799 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x799 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x800 = x797 - x799;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x801 = x800 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x802 = Fp(x801.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x802);
            reg = x802;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x803 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x803 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x804 = x801 - x803;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x805 = x804 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x805);
          reg = x805;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x806 = x7 - x788;
      if (x806 != 0) {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x807 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x807 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x808 = x7 - x807;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x809 = x5 - x807;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x810 = x808 * x809;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x810 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x811 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x811 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x812 = x773 - x811;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x812 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x813 = args[2][137 * steps + ((cycle - 0) & mask)];
        assert(x813 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x814 = x813 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x815 = x814 + x807;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x816 = x774 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x817 = x815 - x816;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x818 = x817 + x775;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x819 = Fp(x818.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x819);
            reg = x819;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x820 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x820 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x821 = x818 - x820;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x822 = x821 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x823 = Fp(x822.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x823);
            reg = x823;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x824 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x824 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x825 = x822 - x824;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x826 = x825 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x827 = Fp(x826.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x827);
            reg = x827;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x828 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x828 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x829 = x826 - x828;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x830 = x829 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x830);
          reg = x830;
        }
        if (x809 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x831 = x776 - x780;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x831 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x832 = x777 - x781;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x832 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x833 = x778 - x782;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x833 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x834 = x779 - x783;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x834 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("cirgen/components/ram.cpp":51:40))
      auto x835 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x835 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x836 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x836 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x837 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x837 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x838 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x838 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x839 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x839 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x840 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x840 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x841 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x841 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x842 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x842 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x843 = x835 - x842;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x844 = (x843 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x845 = x7 - x844;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x845);
          reg = x845;
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x846 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x846 != Fp::invalid());
      if (x846 != 0) {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x847 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x847 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x848 = x6 - x847;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x848 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x849 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x849 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x850 = x849 - x835;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x851 = x850 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x852 = Fp(x851.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x852);
            reg = x852;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x853 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x853 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x854 = x851 - x853;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x855 = x854 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x856 = Fp(x855.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x856);
            reg = x856;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x857 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x857 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x858 = x855 - x857;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x859 = x858 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x860 = Fp(x859.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x860);
            reg = x860;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x861 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x861 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x862 = x859 - x861;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x863 = x862 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x863);
          reg = x863;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x864 = x7 - x846;
      if (x864 != 0) {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x865 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x865 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x866 = x7 - x865;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x867 = x5 - x865;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x868 = x866 * x867;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x868 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x869 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x869 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x870 = x835 - x869;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x870 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x871 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x871 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x872 = x871 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x873 = x872 + x865;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x874 = x836 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x875 = x873 - x874;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x876 = x875 + x837;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x877 = Fp(x876.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x877);
            reg = x877;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x878 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x878 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x879 = x876 - x878;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x880 = x879 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x881 = Fp(x880.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x881);
            reg = x881;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x882 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x882 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x883 = x880 - x882;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x884 = x883 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x885 = Fp(x884.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x885);
            reg = x885;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x886 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x886 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x887 = x884 - x886;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x888 = x887 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x888);
          reg = x888;
        }
        if (x867 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x889 = x780 - x838;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x889 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x890 = x781 - x839;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x890 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x891 = x782 - x840;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x891 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x892 = x783 - x841;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x892 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("cirgen/components/ram.cpp":51:40))
      auto x893 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x893 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x894 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x894 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x895 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x895 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x896 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x896 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x897 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x897 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x898 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x898 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x899 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x899 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x900 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x900 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x901 = x893 - x900;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x902 = (x901 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x903 = x7 - x902;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x903);
          reg = x903;
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x904 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x904 != Fp::invalid());
      if (x904 != 0) {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x905 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x905 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x906 = x6 - x905;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x906 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x907 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x907 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x908 = x907 - x893;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x909 = x908 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x910 = Fp(x909.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x910);
            reg = x910;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x911 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x911 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x912 = x909 - x911;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x913 = x912 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x914 = Fp(x913.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x914);
            reg = x914;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x915 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x915 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x916 = x913 - x915;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x917 = x916 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x918 = Fp(x917.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x918);
            reg = x918;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x919 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x919 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x920 = x917 - x919;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x921 = x920 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x921);
          reg = x921;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x922 = x7 - x904;
      if (x922 != 0) {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x923 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x923 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x924 = x7 - x923;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x925 = x5 - x923;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x926 = x924 * x925;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x926 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x927 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x927 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x928 = x893 - x927;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x928 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x929 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x929 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x930 = x929 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x931 = x930 + x923;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x932 = x894 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x933 = x931 - x932;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x934 = x933 + x895;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x935 = Fp(x934.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x935);
            reg = x935;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x936 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x936 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x937 = x934 - x936;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x938 = x937 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x939 = Fp(x938.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x939);
            reg = x939;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x940 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x940 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x941 = x938 - x940;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x942 = x941 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x943 = Fp(x942.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x943);
            reg = x943;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x944 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x944 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x945 = x942 - x944;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x946 = x945 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x946);
          reg = x946;
        }
        if (x925 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x947 = x838 - x896;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x947 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x948 = x839 - x897;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x948 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x949 = x840 - x898;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x949 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x950 = x841 - x899;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x950 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("cirgen/components/ram.cpp":51:40))
      auto x951 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x951 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x952 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x952 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x953 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x953 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x954 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x954 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x955 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x955 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x956 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x956 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x957 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x957 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x958 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x958 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x959 = x951 - x958;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x960 = (x959 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x961 = x7 - x960;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x961);
          reg = x961;
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x962 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x962 != Fp::invalid());
      if (x962 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x963 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x963 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x964 = x6 - x963;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x964 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x965 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x965 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x966 = x965 - x951;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x967 = x966 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x968 = Fp(x967.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x968);
            reg = x968;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x969 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x969 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x970 = x967 - x969;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x971 = x970 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x972 = Fp(x971.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x972);
            reg = x972;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x973 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x973 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x974 = x971 - x973;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x975 = x974 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x976 = Fp(x975.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x976);
            reg = x976;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x977 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x977 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x978 = x975 - x977;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x979 = x978 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x979);
          reg = x979;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x980 = x7 - x962;
      if (x980 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x981 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x981 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x982 = x7 - x981;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x983 = x5 - x981;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x984 = x982 * x983;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x984 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x985 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x985 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x986 = x951 - x985;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x986 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x987 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x987 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x988 = x987 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x989 = x988 + x981;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x990 = x952 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x991 = x989 - x990;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x992 = x991 + x953;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x993 = Fp(x992.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x993);
            reg = x993;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x994 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x994 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x995 = x992 - x994;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x996 = x995 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x997 = Fp(x996.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x997);
            reg = x997;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x998 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x998 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x999 = x996 - x998;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1000 = x999 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1001 = Fp(x1000.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1001);
            reg = x1001;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1002 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1002 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1003 = x1000 - x1002;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1004 = x1003 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1004);
          reg = x1004;
        }
        if (x983 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1005 = x896 - x954;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1005 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1006 = x897 - x955;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1006 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1007 = x898 - x956;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1007 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1008 = x899 - x957;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1008 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x1009 = args[2][95 * steps + ((cycle - 0) & mask)];
    assert(x1009 != Fp::invalid());
    if (x1009 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1010 = host_outs.at(0);
        auto x1011 = host_outs.at(1);
        auto x1012 = host_outs.at(2);
        auto x1013 = host_outs.at(3);
        auto x1014 = host_outs.at(4);
        auto x1015 = host_outs.at(5);
        auto x1016 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1010);
          reg = x1010;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1011);
          reg = x1011;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1012);
          reg = x1012;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1013);
          reg = x1013;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1014);
          reg = x1014;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][141 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1015);
          reg = x1015;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1016);
          reg = x1016;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1017 = host_outs.at(0);
        auto x1018 = host_outs.at(1);
        auto x1019 = host_outs.at(2);
        auto x1020 = host_outs.at(3);
        auto x1021 = host_outs.at(4);
        auto x1022 = host_outs.at(5);
        auto x1023 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1017);
          reg = x1017;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1018);
          reg = x1018;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1019);
          reg = x1019;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1020);
          reg = x1020;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1021);
          reg = x1021;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1022);
          reg = x1022;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1023);
          reg = x1023;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1024 = host_outs.at(0);
        auto x1025 = host_outs.at(1);
        auto x1026 = host_outs.at(2);
        auto x1027 = host_outs.at(3);
        auto x1028 = host_outs.at(4);
        auto x1029 = host_outs.at(5);
        auto x1030 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1024);
          reg = x1024;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1025);
          reg = x1025;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1026);
          reg = x1026;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1027);
          reg = x1027;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1028);
          reg = x1028;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1029);
          reg = x1029;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1030);
          reg = x1030;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1031 = host_outs.at(0);
        auto x1032 = host_outs.at(1);
        auto x1033 = host_outs.at(2);
        auto x1034 = host_outs.at(3);
        auto x1035 = host_outs.at(4);
        auto x1036 = host_outs.at(5);
        auto x1037 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1031);
          reg = x1031;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1032);
          reg = x1032;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1033);
          reg = x1033;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1034);
          reg = x1034;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1035);
          reg = x1035;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1036);
          reg = x1036;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1037);
          reg = x1037;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1038 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x1038 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x1039 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x1039 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x1040 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x1040 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1041 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x1041 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1042 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x1042 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1043 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x1043 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1044 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x1044 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1045 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x1045 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1046 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x1046 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1047 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x1047 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1048 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x1048 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1049 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x1049 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1050 = x1038 - x1049;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1051 = (x1050 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1052 = x7 - x1051;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1052);
          reg = x1052;
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1053 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x1053 != Fp::invalid());
      if (x1053 != 0) {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1054 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x1054 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1055 = x6 - x1054;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1055 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1056 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x1056 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1057 = x1056 - x1038;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1058 = x1057 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1059 = Fp(x1058.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1059);
            reg = x1059;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1060 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1060 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1061 = x1058 - x1060;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1062 = x1061 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1063 = Fp(x1062.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1063);
            reg = x1063;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1064 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1064 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1065 = x1062 - x1064;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1066 = x1065 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1067 = Fp(x1066.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1067);
            reg = x1067;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1068 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1068 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1069 = x1066 - x1068;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1070 = x1069 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1070);
          reg = x1070;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1071 = x7 - x1053;
      if (x1071 != 0) {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1072 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x1072 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1073 = x7 - x1072;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1074 = x5 - x1072;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1075 = x1073 * x1074;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1075 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1076 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x1076 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1077 = x1038 - x1076;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1077 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1078 = args[2][137 * steps + ((cycle - 0) & mask)];
        assert(x1078 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1079 = x1078 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1080 = x1079 + x1072;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1081 = x1039 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1082 = x1080 - x1081;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1083 = x1082 + x1040;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1084 = Fp(x1083.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1084);
            reg = x1084;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1085 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1085 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1086 = x1083 - x1085;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1087 = x1086 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1088 = Fp(x1087.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1088);
            reg = x1088;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1089 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1089 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1090 = x1087 - x1089;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1091 = x1090 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1092 = Fp(x1091.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1092);
            reg = x1092;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1093 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1093 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1094 = x1091 - x1093;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1095 = x1094 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1095);
          reg = x1095;
        }
        if (x1074 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1096 = x1041 - x1045;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1096 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1097 = x1042 - x1046;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1097 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1098 = x1043 - x1047;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1098 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1099 = x1044 - x1048;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1099 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1100 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x1100 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x1101 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x1101 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x1102 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x1102 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1103 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x1103 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1104 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x1104 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1105 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x1105 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1106 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x1106 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1107 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1107 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1108 = x1100 - x1107;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1109 = (x1108 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1110 = x7 - x1109;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1110);
          reg = x1110;
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1111 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x1111 != Fp::invalid());
      if (x1111 != 0) {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1112 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x1112 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1113 = x6 - x1112;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1113 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1114 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1114 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1115 = x1114 - x1100;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1116 = x1115 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1117 = Fp(x1116.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1117);
            reg = x1117;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1118 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x1118 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1119 = x1116 - x1118;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1120 = x1119 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1121 = Fp(x1120.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1121);
            reg = x1121;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1122 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x1122 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1123 = x1120 - x1122;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1124 = x1123 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1125 = Fp(x1124.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1125);
            reg = x1125;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1126 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x1126 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1127 = x1124 - x1126;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1128 = x1127 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1128);
          reg = x1128;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1129 = x7 - x1111;
      if (x1129 != 0) {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1130 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x1130 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1131 = x7 - x1130;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1132 = x5 - x1130;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1133 = x1131 * x1132;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1133 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1134 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1134 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1135 = x1100 - x1134;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1135 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1136 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x1136 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1137 = x1136 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1138 = x1137 + x1130;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1139 = x1101 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1140 = x1138 - x1139;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1141 = x1140 + x1102;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1142 = Fp(x1141.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1142);
            reg = x1142;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1143 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x1143 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1144 = x1141 - x1143;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1145 = x1144 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1146 = Fp(x1145.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1146);
            reg = x1146;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1147 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x1147 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1148 = x1145 - x1147;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1149 = x1148 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1150 = Fp(x1149.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1150);
            reg = x1150;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1151 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x1151 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1152 = x1149 - x1151;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1153 = x1152 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1153);
          reg = x1153;
        }
        if (x1132 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1154 = x1045 - x1103;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1154 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1155 = x1046 - x1104;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1155 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1156 = x1047 - x1105;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1156 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1157 = x1048 - x1106;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1157 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1158 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x1158 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x1159 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x1159 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x1160 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x1160 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1161 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x1161 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1162 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x1162 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1163 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x1163 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1164 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x1164 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1165 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1165 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1166 = x1158 - x1165;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1167 = (x1166 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1168 = x7 - x1167;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1168);
          reg = x1168;
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1169 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x1169 != Fp::invalid());
      if (x1169 != 0) {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1170 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x1170 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1171 = x6 - x1170;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1171 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1172 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1172 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1173 = x1172 - x1158;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1174 = x1173 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1175 = Fp(x1174.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1175);
            reg = x1175;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1176 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x1176 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1177 = x1174 - x1176;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1178 = x1177 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1179 = Fp(x1178.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1179);
            reg = x1179;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1180 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x1180 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1181 = x1178 - x1180;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1182 = x1181 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1183 = Fp(x1182.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1183);
            reg = x1183;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1184 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x1184 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1185 = x1182 - x1184;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1186 = x1185 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1186);
          reg = x1186;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1187 = x7 - x1169;
      if (x1187 != 0) {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1188 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x1188 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1189 = x7 - x1188;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1190 = x5 - x1188;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1191 = x1189 * x1190;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1191 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1192 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1192 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1193 = x1158 - x1192;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1193 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1194 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x1194 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1195 = x1194 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1196 = x1195 + x1188;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1197 = x1159 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1198 = x1196 - x1197;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1199 = x1198 + x1160;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1200 = Fp(x1199.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1200);
            reg = x1200;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1201 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x1201 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1202 = x1199 - x1201;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1203 = x1202 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1204 = Fp(x1203.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1204);
            reg = x1204;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1205 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x1205 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1206 = x1203 - x1205;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1207 = x1206 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1208 = Fp(x1207.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1208);
            reg = x1208;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1209 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x1209 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1210 = x1207 - x1209;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1211 = x1210 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1211);
          reg = x1211;
        }
        if (x1190 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1212 = x1103 - x1161;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1212 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1213 = x1104 - x1162;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1213 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1214 = x1105 - x1163;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1214 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1215 = x1106 - x1164;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1215 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1216 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x1216 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x1217 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x1217 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x1218 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x1218 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1219 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x1219 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1220 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x1220 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1221 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x1221 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1222 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x1222 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1223 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1223 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1224 = x1216 - x1223;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1225 = (x1224 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1226 = x7 - x1225;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1226);
          reg = x1226;
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1227 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x1227 != Fp::invalid());
      if (x1227 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1228 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x1228 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1229 = x6 - x1228;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1229 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1230 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1230 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1231 = x1230 - x1216;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1232 = x1231 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1233 = Fp(x1232.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1233);
            reg = x1233;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1234 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1234 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1235 = x1232 - x1234;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1236 = x1235 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1237 = Fp(x1236.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1237);
            reg = x1237;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1238 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1238 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1239 = x1236 - x1238;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1240 = x1239 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1241 = Fp(x1240.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1241);
            reg = x1241;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1242 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1242 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1243 = x1240 - x1242;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1244 = x1243 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1244);
          reg = x1244;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1245 = x7 - x1227;
      if (x1245 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1246 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x1246 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1247 = x7 - x1246;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1248 = x5 - x1246;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1249 = x1247 * x1248;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1249 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1250 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1250 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1251 = x1216 - x1250;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1251 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1252 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x1252 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1253 = x1252 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1254 = x1253 + x1246;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1255 = x1217 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1256 = x1254 - x1255;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1257 = x1256 + x1218;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1258 = Fp(x1257.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1258);
            reg = x1258;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1259 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1259 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1260 = x1257 - x1259;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1261 = x1260 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1262 = Fp(x1261.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1262);
            reg = x1262;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1263 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1263 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1264 = x1261 - x1263;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1265 = x1264 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1266 = Fp(x1265.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1266);
            reg = x1266;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1267 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1267 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1268 = x1265 - x1267;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1269 = x1268 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1269);
          reg = x1269;
        }
        if (x1248 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1270 = x1161 - x1219;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1270 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1271 = x1162 - x1220;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1271 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1272 = x1163 - x1221;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1272 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1273 = x1164 - x1222;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1273 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x1274 = args[2][96 * steps + ((cycle - 0) & mask)];
    assert(x1274 != Fp::invalid());
    if (x1274 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1275 = host_outs.at(0);
        auto x1276 = host_outs.at(1);
        auto x1277 = host_outs.at(2);
        auto x1278 = host_outs.at(3);
        auto x1279 = host_outs.at(4);
        auto x1280 = host_outs.at(5);
        auto x1281 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1275);
          reg = x1275;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1276);
          reg = x1276;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1277);
          reg = x1277;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1278);
          reg = x1278;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1279);
          reg = x1279;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][141 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1280);
          reg = x1280;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1281);
          reg = x1281;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1282 = host_outs.at(0);
        auto x1283 = host_outs.at(1);
        auto x1284 = host_outs.at(2);
        auto x1285 = host_outs.at(3);
        auto x1286 = host_outs.at(4);
        auto x1287 = host_outs.at(5);
        auto x1288 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1282);
          reg = x1282;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1283);
          reg = x1283;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1284);
          reg = x1284;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1285);
          reg = x1285;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1286);
          reg = x1286;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1287);
          reg = x1287;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1288);
          reg = x1288;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1289 = host_outs.at(0);
        auto x1290 = host_outs.at(1);
        auto x1291 = host_outs.at(2);
        auto x1292 = host_outs.at(3);
        auto x1293 = host_outs.at(4);
        auto x1294 = host_outs.at(5);
        auto x1295 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1289);
          reg = x1289;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1290);
          reg = x1290;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1291);
          reg = x1291;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1292);
          reg = x1292;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1293);
          reg = x1293;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1294);
          reg = x1294;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1295);
          reg = x1295;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1296 = host_outs.at(0);
        auto x1297 = host_outs.at(1);
        auto x1298 = host_outs.at(2);
        auto x1299 = host_outs.at(3);
        auto x1300 = host_outs.at(4);
        auto x1301 = host_outs.at(5);
        auto x1302 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1296);
          reg = x1296;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1297);
          reg = x1297;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1298);
          reg = x1298;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1299);
          reg = x1299;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1300);
          reg = x1300;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1301);
          reg = x1301;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1302);
          reg = x1302;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1303 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x1303 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x1304 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x1304 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x1305 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x1305 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1306 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x1306 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1307 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x1307 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1308 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x1308 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1309 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x1309 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1310 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x1310 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1311 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x1311 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1312 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x1312 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1313 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x1313 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1314 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x1314 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1315 = x1303 - x1314;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1316 = (x1315 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1317 = x7 - x1316;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1317);
          reg = x1317;
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1318 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x1318 != Fp::invalid());
      if (x1318 != 0) {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1319 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x1319 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1320 = x6 - x1319;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1320 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1321 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x1321 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1322 = x1321 - x1303;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1323 = x1322 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1324 = Fp(x1323.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1324);
            reg = x1324;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1325 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1325 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1326 = x1323 - x1325;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1327 = x1326 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1328 = Fp(x1327.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1328);
            reg = x1328;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1329 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1329 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1330 = x1327 - x1329;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1331 = x1330 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1332 = Fp(x1331.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1332);
            reg = x1332;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1333 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1333 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1334 = x1331 - x1333;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1335 = x1334 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1335);
          reg = x1335;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1336 = x7 - x1318;
      if (x1336 != 0) {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1337 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x1337 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1338 = x7 - x1337;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1339 = x5 - x1337;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1340 = x1338 * x1339;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1340 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1341 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x1341 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1342 = x1303 - x1341;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1342 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1343 = args[2][137 * steps + ((cycle - 0) & mask)];
        assert(x1343 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1344 = x1343 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1345 = x1344 + x1337;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1346 = x1304 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1347 = x1345 - x1346;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1348 = x1347 + x1305;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1349 = Fp(x1348.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1349);
            reg = x1349;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1350 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1350 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1351 = x1348 - x1350;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1352 = x1351 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1353 = Fp(x1352.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1353);
            reg = x1353;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1354 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1354 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1355 = x1352 - x1354;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1356 = x1355 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1357 = Fp(x1356.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1357);
            reg = x1357;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1358 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1358 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1359 = x1356 - x1358;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1360 = x1359 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1360);
          reg = x1360;
        }
        if (x1339 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1361 = x1306 - x1310;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1361 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1362 = x1307 - x1311;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1362 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1363 = x1308 - x1312;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1363 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1364 = x1309 - x1313;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1364 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1365 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x1365 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x1366 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x1366 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x1367 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x1367 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1368 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x1368 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1369 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x1369 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1370 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x1370 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1371 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x1371 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1372 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1372 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1373 = x1365 - x1372;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1374 = (x1373 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1375 = x7 - x1374;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1375);
          reg = x1375;
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1376 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x1376 != Fp::invalid());
      if (x1376 != 0) {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1377 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x1377 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1378 = x6 - x1377;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1378 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1379 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1379 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1380 = x1379 - x1365;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1381 = x1380 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1382 = Fp(x1381.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1382);
            reg = x1382;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1383 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x1383 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1384 = x1381 - x1383;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1385 = x1384 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1386 = Fp(x1385.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1386);
            reg = x1386;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1387 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x1387 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1388 = x1385 - x1387;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1389 = x1388 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1390 = Fp(x1389.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1390);
            reg = x1390;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1391 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x1391 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1392 = x1389 - x1391;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1393 = x1392 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1393);
          reg = x1393;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1394 = x7 - x1376;
      if (x1394 != 0) {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1395 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x1395 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1396 = x7 - x1395;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1397 = x5 - x1395;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1398 = x1396 * x1397;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1398 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1399 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1399 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1400 = x1365 - x1399;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1400 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1401 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x1401 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1402 = x1401 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1403 = x1402 + x1395;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1404 = x1366 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1405 = x1403 - x1404;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1406 = x1405 + x1367;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1407 = Fp(x1406.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1407);
            reg = x1407;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1408 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x1408 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1409 = x1406 - x1408;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1410 = x1409 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1411 = Fp(x1410.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1411);
            reg = x1411;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1412 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x1412 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1413 = x1410 - x1412;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1414 = x1413 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1415 = Fp(x1414.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1415);
            reg = x1415;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1416 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x1416 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1417 = x1414 - x1416;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1418 = x1417 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1418);
          reg = x1418;
        }
        if (x1397 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1419 = x1310 - x1368;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1419 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1420 = x1311 - x1369;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1420 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1421 = x1312 - x1370;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1421 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1422 = x1313 - x1371;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1422 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1423 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x1423 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x1424 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x1424 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x1425 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x1425 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1426 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x1426 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1427 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x1427 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1428 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x1428 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1429 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x1429 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1430 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1430 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1431 = x1423 - x1430;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1432 = (x1431 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1433 = x7 - x1432;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1433);
          reg = x1433;
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1434 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x1434 != Fp::invalid());
      if (x1434 != 0) {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1435 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x1435 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1436 = x6 - x1435;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1436 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1437 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1437 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1438 = x1437 - x1423;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1439 = x1438 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1440 = Fp(x1439.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1440);
            reg = x1440;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1441 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x1441 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1442 = x1439 - x1441;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1443 = x1442 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1444 = Fp(x1443.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1444);
            reg = x1444;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1445 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x1445 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1446 = x1443 - x1445;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1447 = x1446 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1448 = Fp(x1447.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1448);
            reg = x1448;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1449 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x1449 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1450 = x1447 - x1449;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1451 = x1450 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1451);
          reg = x1451;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1452 = x7 - x1434;
      if (x1452 != 0) {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1453 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x1453 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1454 = x7 - x1453;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1455 = x5 - x1453;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1456 = x1454 * x1455;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1456 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1457 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1457 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1458 = x1423 - x1457;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1458 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1459 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x1459 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1460 = x1459 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1461 = x1460 + x1453;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1462 = x1424 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1463 = x1461 - x1462;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1464 = x1463 + x1425;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1465 = Fp(x1464.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1465);
            reg = x1465;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1466 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x1466 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1467 = x1464 - x1466;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1468 = x1467 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1469 = Fp(x1468.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1469);
            reg = x1469;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1470 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x1470 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1471 = x1468 - x1470;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1472 = x1471 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1473 = Fp(x1472.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1473);
            reg = x1473;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1474 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x1474 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1475 = x1472 - x1474;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1476 = x1475 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1476);
          reg = x1476;
        }
        if (x1455 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1477 = x1368 - x1426;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1477 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1478 = x1369 - x1427;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1478 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1479 = x1370 - x1428;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1479 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1480 = x1371 - x1429;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1480 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1481 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x1481 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x1482 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x1482 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x1483 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x1483 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1484 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x1484 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1485 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x1485 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1486 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x1486 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1487 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x1487 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1488 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1488 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1489 = x1481 - x1488;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1490 = (x1489 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1491 = x7 - x1490;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1491);
          reg = x1491;
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1492 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x1492 != Fp::invalid());
      if (x1492 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1493 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x1493 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1494 = x6 - x1493;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1494 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1495 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1495 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1496 = x1495 - x1481;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1497 = x1496 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1498 = Fp(x1497.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1498);
            reg = x1498;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1499 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1499 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1500 = x1497 - x1499;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1501 = x1500 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1502 = Fp(x1501.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1502);
            reg = x1502;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1503 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1503 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1504 = x1501 - x1503;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1505 = x1504 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1506 = Fp(x1505.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1506);
            reg = x1506;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1507 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1507 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1508 = x1505 - x1507;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1509 = x1508 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1509);
          reg = x1509;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1510 = x7 - x1492;
      if (x1510 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1511 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x1511 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1512 = x7 - x1511;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1513 = x5 - x1511;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1514 = x1512 * x1513;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1514 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1515 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1515 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1516 = x1481 - x1515;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1516 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1517 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x1517 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1518 = x1517 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1519 = x1518 + x1511;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1520 = x1482 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1521 = x1519 - x1520;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1522 = x1521 + x1483;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1523 = Fp(x1522.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1523);
            reg = x1523;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1524 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1524 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1525 = x1522 - x1524;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1526 = x1525 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1527 = Fp(x1526.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1527);
            reg = x1527;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1528 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1528 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1529 = x1526 - x1528;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1530 = x1529 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1531 = Fp(x1530.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1531);
            reg = x1531;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1532 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1532 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1533 = x1530 - x1532;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1534 = x1533 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1534);
          reg = x1534;
        }
        if (x1513 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1535 = x1426 - x1484;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1535 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1536 = x1427 - x1485;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1536 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1537 = x1428 - x1486;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1537 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1538 = x1429 - x1487;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1538 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x1539 = args[2][97 * steps + ((cycle - 0) & mask)];
    assert(x1539 != Fp::invalid());
    if (x1539 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1540 = host_outs.at(0);
        auto x1541 = host_outs.at(1);
        auto x1542 = host_outs.at(2);
        auto x1543 = host_outs.at(3);
        auto x1544 = host_outs.at(4);
        auto x1545 = host_outs.at(5);
        auto x1546 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1540);
          reg = x1540;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1541);
          reg = x1541;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1542);
          reg = x1542;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1543);
          reg = x1543;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1544);
          reg = x1544;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1545);
          reg = x1545;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1546);
          reg = x1546;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1547 = host_outs.at(0);
        auto x1548 = host_outs.at(1);
        auto x1549 = host_outs.at(2);
        auto x1550 = host_outs.at(3);
        auto x1551 = host_outs.at(4);
        auto x1552 = host_outs.at(5);
        auto x1553 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1547);
          reg = x1547;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1548);
          reg = x1548;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1549);
          reg = x1549;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1550);
          reg = x1550;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1551);
          reg = x1551;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1552);
          reg = x1552;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1553);
          reg = x1553;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1554 = host_outs.at(0);
        auto x1555 = host_outs.at(1);
        auto x1556 = host_outs.at(2);
        auto x1557 = host_outs.at(3);
        auto x1558 = host_outs.at(4);
        auto x1559 = host_outs.at(5);
        auto x1560 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1554);
          reg = x1554;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1555);
          reg = x1555;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1556);
          reg = x1556;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1557);
          reg = x1557;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][161 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1558);
          reg = x1558;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][162 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1559);
          reg = x1559;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][163 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1560);
          reg = x1560;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1561 = host_outs.at(0);
        auto x1562 = host_outs.at(1);
        auto x1563 = host_outs.at(2);
        auto x1564 = host_outs.at(3);
        auto x1565 = host_outs.at(4);
        auto x1566 = host_outs.at(5);
        auto x1567 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][164 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1561);
          reg = x1561;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][165 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1562);
          reg = x1562;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][166 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1563);
          reg = x1563;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][167 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1564);
          reg = x1564;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1565);
          reg = x1565;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][169 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1566);
          reg = x1566;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1567);
          reg = x1567;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1568 = host_outs.at(0);
        auto x1569 = host_outs.at(1);
        auto x1570 = host_outs.at(2);
        auto x1571 = host_outs.at(3);
        auto x1572 = host_outs.at(4);
        auto x1573 = host_outs.at(5);
        auto x1574 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1568);
          reg = x1568;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1569);
          reg = x1569;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1570);
          reg = x1570;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1571);
          reg = x1571;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1572);
          reg = x1572;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1573);
          reg = x1573;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1574);
          reg = x1574;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1575 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x1575 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x1576 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x1576 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x1577 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x1577 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1578 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x1578 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1579 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x1579 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1580 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x1580 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1581 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x1581 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1582 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x1582 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1583 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x1583 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1584 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x1584 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1585 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x1585 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1586 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1586 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1587 = x1575 - x1586;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1588 = (x1587 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1589 = x7 - x1588;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][171 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1589);
          reg = x1589;
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1590 = args[2][171 * steps + ((cycle - 0) & mask)];
      assert(x1590 != Fp::invalid());
      if (x1590 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1591 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x1591 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1592 = x6 - x1591;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1592 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1593 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1593 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1594 = x1593 - x1575;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1595 = x1594 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1596 = Fp(x1595.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1596);
            reg = x1596;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1597 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1597 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1598 = x1595 - x1597;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1599 = x1598 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1600 = Fp(x1599.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1600);
            reg = x1600;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1601 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1601 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1602 = x1599 - x1601;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1603 = x1602 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1604 = Fp(x1603.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1604);
            reg = x1604;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1605 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1605 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1606 = x1603 - x1605;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1607 = x1606 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1607);
          reg = x1607;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1608 = x7 - x1590;
      if (x1608 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1609 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x1609 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1610 = x7 - x1609;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1611 = x5 - x1609;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1612 = x1610 * x1611;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1612 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1613 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1613 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1614 = x1575 - x1613;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1614 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1615 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x1615 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1616 = x1615 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1617 = x1616 + x1609;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1618 = x1576 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1619 = x1617 - x1618;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1620 = x1619 + x1577;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1621 = Fp(x1620.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1621);
            reg = x1621;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1622 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1622 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1623 = x1620 - x1622;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1624 = x1623 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1625 = Fp(x1624.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1625);
            reg = x1625;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1626 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1626 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1627 = x1624 - x1626;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1628 = x1627 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1629 = Fp(x1628.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1629);
            reg = x1629;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1630 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1630 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1631 = x1628 - x1630;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1632 = x1631 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1632);
          reg = x1632;
        }
        if (x1611 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1633 = x1578 - x1582;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1633 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1634 = x1579 - x1583;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1634 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1635 = x1580 - x1584;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1635 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1636 = x1581 - x1585;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1636 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1637 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x1637 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x1638 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x1638 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x1639 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x1639 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1640 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x1640 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1641 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x1641 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1642 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x1642 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1643 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x1643 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1644 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1644 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1645 = x1637 - x1644;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1646 = (x1645 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1647 = x7 - x1646;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1647);
          reg = x1647;
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1648 = args[2][172 * steps + ((cycle - 0) & mask)];
      assert(x1648 != Fp::invalid());
      if (x1648 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1649 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x1649 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1650 = x6 - x1649;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1650 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1651 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1651 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1652 = x1651 - x1637;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1653 = x1652 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1654 = Fp(x1653.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1654);
            reg = x1654;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1655 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x1655 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1656 = x1653 - x1655;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1657 = x1656 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1658 = Fp(x1657.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1658);
            reg = x1658;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1659 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x1659 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1660 = x1657 - x1659;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1661 = x1660 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1662 = Fp(x1661.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1662);
            reg = x1662;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1663 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x1663 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1664 = x1661 - x1663;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1665 = x1664 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1665);
          reg = x1665;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1666 = x7 - x1648;
      if (x1666 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1667 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x1667 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1668 = x7 - x1667;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1669 = x5 - x1667;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1670 = x1668 * x1669;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1670 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1671 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1671 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1672 = x1637 - x1671;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1672 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1673 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x1673 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1674 = x1673 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1675 = x1674 + x1667;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1676 = x1638 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1677 = x1675 - x1676;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1678 = x1677 + x1639;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1679 = Fp(x1678.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1679);
            reg = x1679;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1680 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x1680 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1681 = x1678 - x1680;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1682 = x1681 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1683 = Fp(x1682.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1683);
            reg = x1683;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1684 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x1684 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1685 = x1682 - x1684;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1686 = x1685 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1687 = Fp(x1686.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1687);
            reg = x1687;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1688 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x1688 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1689 = x1686 - x1688;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1690 = x1689 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1690);
          reg = x1690;
        }
        if (x1669 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1691 = x1582 - x1640;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1691 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1692 = x1583 - x1641;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1692 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1693 = x1584 - x1642;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1693 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1694 = x1585 - x1643;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1694 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1695 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x1695 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x1696 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x1696 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x1697 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x1697 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1698 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x1698 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1699 = args[2][161 * steps + ((cycle - 0) & mask)];
      assert(x1699 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1700 = args[2][162 * steps + ((cycle - 0) & mask)];
      assert(x1700 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1701 = args[2][163 * steps + ((cycle - 0) & mask)];
      assert(x1701 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1702 = args[2][157 * steps + ((cycle - 0) & mask)];
        assert(x1702 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1703 = x1695 - x1702;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1704 = (x1703 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1705 = x7 - x1704;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][173 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1705);
          reg = x1705;
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1706 = args[2][173 * steps + ((cycle - 0) & mask)];
      assert(x1706 != Fp::invalid());
      if (x1706 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1707 = args[2][159 * steps + ((cycle - 0) & mask)];
        assert(x1707 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1708 = x6 - x1707;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1708 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1709 = args[2][157 * steps + ((cycle - 0) & mask)];
        assert(x1709 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1710 = x1709 - x1695;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1711 = x1710 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1712 = Fp(x1711.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1712);
            reg = x1712;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1713 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x1713 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1714 = x1711 - x1713;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1715 = x1714 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1716 = Fp(x1715.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1716);
            reg = x1716;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1717 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x1717 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1718 = x1715 - x1717;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1719 = x1718 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1720 = Fp(x1719.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1720);
            reg = x1720;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1721 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x1721 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1722 = x1719 - x1721;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1723 = x1722 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1723);
          reg = x1723;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1724 = x7 - x1706;
      if (x1724 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1725 = args[2][159 * steps + ((cycle - 0) & mask)];
        assert(x1725 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1726 = x7 - x1725;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1727 = x5 - x1725;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1728 = x1726 * x1727;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1728 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1729 = args[2][157 * steps + ((cycle - 0) & mask)];
        assert(x1729 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1730 = x1695 - x1729;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1730 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1731 = args[2][158 * steps + ((cycle - 0) & mask)];
        assert(x1731 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1732 = x1731 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1733 = x1732 + x1725;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1734 = x1696 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1735 = x1733 - x1734;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1736 = x1735 + x1697;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1737 = Fp(x1736.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1737);
            reg = x1737;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1738 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x1738 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1739 = x1736 - x1738;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1740 = x1739 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1741 = Fp(x1740.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1741);
            reg = x1741;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1742 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x1742 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1743 = x1740 - x1742;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1744 = x1743 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1745 = Fp(x1744.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1745);
            reg = x1745;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1746 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x1746 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1747 = x1744 - x1746;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1748 = x1747 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1748);
          reg = x1748;
        }
        if (x1727 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1749 = x1640 - x1698;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1749 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1750 = x1641 - x1699;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1750 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1751 = x1642 - x1700;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1751 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1752 = x1643 - x1701;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1752 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1753 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x1753 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x1754 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x1754 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x1755 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x1755 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1756 = args[2][167 * steps + ((cycle - 0) & mask)];
      assert(x1756 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1757 = args[2][168 * steps + ((cycle - 0) & mask)];
      assert(x1757 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1758 = args[2][169 * steps + ((cycle - 0) & mask)];
      assert(x1758 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1759 = args[2][170 * steps + ((cycle - 0) & mask)];
      assert(x1759 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1760 = args[2][164 * steps + ((cycle - 0) & mask)];
        assert(x1760 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1761 = x1753 - x1760;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1762 = (x1761 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1763 = x7 - x1762;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][174 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1763);
          reg = x1763;
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkVerifier3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1764 = args[2][174 * steps + ((cycle - 0) & mask)];
      assert(x1764 != Fp::invalid());
      if (x1764 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1765 = args[2][166 * steps + ((cycle - 0) & mask)];
        assert(x1765 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1766 = x6 - x1765;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1766 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1767 = args[2][164 * steps + ((cycle - 0) & mask)];
        assert(x1767 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1768 = x1767 - x1753;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1769 = x1768 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1770 = Fp(x1769.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1770);
            reg = x1770;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1771 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1771 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1772 = x1769 - x1771;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1773 = x1772 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1774 = Fp(x1773.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1774);
            reg = x1774;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1775 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1775 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1776 = x1773 - x1775;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1777 = x1776 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1778 = Fp(x1777.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1778);
            reg = x1778;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1779 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1779 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1780 = x1777 - x1779;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1781 = x1780 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1781);
          reg = x1781;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1782 = x7 - x1764;
      if (x1782 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1783 = args[2][166 * steps + ((cycle - 0) & mask)];
        assert(x1783 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1784 = x7 - x1783;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1785 = x5 - x1783;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1786 = x1784 * x1785;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1786 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1787 = args[2][164 * steps + ((cycle - 0) & mask)];
        assert(x1787 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1788 = x1753 - x1787;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1788 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1789 = args[2][165 * steps + ((cycle - 0) & mask)];
        assert(x1789 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1790 = x1789 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1791 = x1790 + x1783;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1792 = x1754 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1793 = x1791 - x1792;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1794 = x1793 + x1755;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1795 = Fp(x1794.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1795);
            reg = x1795;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1796 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1796 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1797 = x1794 - x1796;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1798 = x1797 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1799 = Fp(x1798.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1799);
            reg = x1799;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1800 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1800 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1801 = x1798 - x1800;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1802 = x1801 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1803 = Fp(x1802.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1803);
            reg = x1803;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1804 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1804 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1805 = x1802 - x1804;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1806 = x1805 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1806);
          reg = x1806;
        }
        if (x1785 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1807 = x1698 - x1756;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1807 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1808 = x1699 - x1757;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1808 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1809 = x1700 - x1758;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1809 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1810 = x1701 - x1759;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1810 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1811 = args[2][164 * steps + ((cycle - 0) & mask)];
      assert(x1811 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x1812 = args[2][165 * steps + ((cycle - 0) & mask)];
      assert(x1812 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x1813 = args[2][166 * steps + ((cycle - 0) & mask)];
      assert(x1813 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1814 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x1814 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1815 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x1815 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1816 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x1816 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1817 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x1817 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1818 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1818 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1819 = x1811 - x1818;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1820 = (x1819 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1821 = x7 - x1820;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][175 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1821);
          reg = x1821;
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkVerifier4/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1822 = args[2][175 * steps + ((cycle - 0) & mask)];
      assert(x1822 != Fp::invalid());
      if (x1822 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1823 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x1823 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1824 = x6 - x1823;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1824 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1825 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1825 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1826 = x1825 - x1811;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1827 = x1826 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1828 = Fp(x1827.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][25 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1828);
            reg = x1828;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1829 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x1829 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1830 = x1827 - x1829;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1831 = x1830 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1832 = Fp(x1831.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][26 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1832);
            reg = x1832;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1833 = args[2][26 * steps + ((cycle - 0) & mask)];
        assert(x1833 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1834 = x1831 - x1833;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1835 = x1834 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1836 = Fp(x1835.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][27 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1836);
            reg = x1836;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1837 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x1837 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1838 = x1835 - x1837;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1839 = x1838 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][78 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1839);
          reg = x1839;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1840 = x7 - x1822;
      if (x1840 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1841 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x1841 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1842 = x7 - x1841;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1843 = x5 - x1841;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1844 = x1842 * x1843;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1844 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1845 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1845 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1846 = x1811 - x1845;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1846 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1847 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x1847 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1848 = x1847 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1849 = x1848 + x1841;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1850 = x1812 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1851 = x1849 - x1850;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1852 = x1851 + x1813;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1853 = Fp(x1852.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][25 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1853);
            reg = x1853;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1854 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x1854 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1855 = x1852 - x1854;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1856 = x1855 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1857 = Fp(x1856.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][26 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1857);
            reg = x1857;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1858 = args[2][26 * steps + ((cycle - 0) & mask)];
        assert(x1858 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1859 = x1856 - x1858;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1860 = x1859 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1861 = Fp(x1860.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][27 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1861);
            reg = x1861;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1862 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x1862 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1863 = x1860 - x1862;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1864 = x1863 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][78 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1864);
          reg = x1864;
        }
        if (x1843 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1865 = x1756 - x1814;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1865 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1866 = x1757 - x1815;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1866 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1867 = x1758 - x1816;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1867 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1868 = x1759 - x1817;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1868 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x1869 = args[2][98 * steps + ((cycle - 0) & mask)];
    assert(x1869 != Fp::invalid());
    if (x1869 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1870 = host_outs.at(0);
        auto x1871 = host_outs.at(1);
        auto x1872 = host_outs.at(2);
        auto x1873 = host_outs.at(3);
        auto x1874 = host_outs.at(4);
        auto x1875 = host_outs.at(5);
        auto x1876 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1870);
          reg = x1870;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1871);
          reg = x1871;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1872);
          reg = x1872;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1873);
          reg = x1873;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1874);
          reg = x1874;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1875);
          reg = x1875;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1876);
          reg = x1876;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1877 = host_outs.at(0);
        auto x1878 = host_outs.at(1);
        auto x1879 = host_outs.at(2);
        auto x1880 = host_outs.at(3);
        auto x1881 = host_outs.at(4);
        auto x1882 = host_outs.at(5);
        auto x1883 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1877);
          reg = x1877;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1878);
          reg = x1878;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1879);
          reg = x1879;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1880);
          reg = x1880;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1881);
          reg = x1881;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1882);
          reg = x1882;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1883);
          reg = x1883;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1884 = host_outs.at(0);
        auto x1885 = host_outs.at(1);
        auto x1886 = host_outs.at(2);
        auto x1887 = host_outs.at(3);
        auto x1888 = host_outs.at(4);
        auto x1889 = host_outs.at(5);
        auto x1890 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1884);
          reg = x1884;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1885);
          reg = x1885;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1886);
          reg = x1886;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1887);
          reg = x1887;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][161 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1888);
          reg = x1888;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][162 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1889);
          reg = x1889;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][163 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1890);
          reg = x1890;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1891 = host_outs.at(0);
        auto x1892 = host_outs.at(1);
        auto x1893 = host_outs.at(2);
        auto x1894 = host_outs.at(3);
        auto x1895 = host_outs.at(4);
        auto x1896 = host_outs.at(5);
        auto x1897 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][164 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1891);
          reg = x1891;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][165 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1892);
          reg = x1892;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][166 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1893);
          reg = x1893;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][167 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1894);
          reg = x1894;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1895);
          reg = x1895;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][169 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1896);
          reg = x1896;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1897);
          reg = x1897;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1898 = host_outs.at(0);
        auto x1899 = host_outs.at(1);
        auto x1900 = host_outs.at(2);
        auto x1901 = host_outs.at(3);
        auto x1902 = host_outs.at(4);
        auto x1903 = host_outs.at(5);
        auto x1904 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1898);
          reg = x1898;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1899);
          reg = x1899;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1900);
          reg = x1900;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1901);
          reg = x1901;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1902);
          reg = x1902;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1903);
          reg = x1903;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1904);
          reg = x1904;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1905 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x1905 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x1906 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x1906 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x1907 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x1907 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1908 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x1908 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1909 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x1909 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1910 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x1910 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1911 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x1911 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1912 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x1912 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1913 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x1913 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1914 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x1914 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1915 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x1915 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1916 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1916 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1917 = x1905 - x1916;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1918 = (x1917 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1919 = x7 - x1918;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][171 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1919);
          reg = x1919;
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1920 = args[2][171 * steps + ((cycle - 0) & mask)];
      assert(x1920 != Fp::invalid());
      if (x1920 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1921 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x1921 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1922 = x6 - x1921;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1922 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1923 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1923 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1924 = x1923 - x1905;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1925 = x1924 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1926 = Fp(x1925.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1926);
            reg = x1926;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1927 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1927 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1928 = x1925 - x1927;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1929 = x1928 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1930 = Fp(x1929.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1930);
            reg = x1930;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1931 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1931 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1932 = x1929 - x1931;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1933 = x1932 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1934 = Fp(x1933.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1934);
            reg = x1934;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1935 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1935 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1936 = x1933 - x1935;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1937 = x1936 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1937);
          reg = x1937;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1938 = x7 - x1920;
      if (x1938 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1939 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x1939 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1940 = x7 - x1939;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1941 = x5 - x1939;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x1942 = x1940 * x1941;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x1942 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1943 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1943 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x1944 = x1905 - x1943;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x1944 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1945 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x1945 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1946 = x1945 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1947 = x1946 + x1939;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x1948 = x1906 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1949 = x1947 - x1948;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x1950 = x1949 + x1907;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1951 = Fp(x1950.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1951);
            reg = x1951;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1952 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1952 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1953 = x1950 - x1952;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1954 = x1953 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1955 = Fp(x1954.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1955);
            reg = x1955;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1956 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1956 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1957 = x1954 - x1956;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1958 = x1957 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1959 = Fp(x1958.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1959);
            reg = x1959;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1960 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1960 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1961 = x1958 - x1960;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1962 = x1961 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1962);
          reg = x1962;
        }
        if (x1941 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1963 = x1908 - x1912;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1963 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1964 = x1909 - x1913;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1964 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1965 = x1910 - x1914;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1965 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x1966 = x1911 - x1915;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x1966 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/Reg"("cirgen/components/ram.cpp":51:40))
      auto x1967 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x1967 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x1968 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x1968 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x1969 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x1969 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1970 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x1970 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1971 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x1971 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1972 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x1972 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1973 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x1973 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1974 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1974 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1975 = x1967 - x1974;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x1976 = (x1975 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x1977 = x7 - x1976;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1977);
          reg = x1977;
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x1978 = args[2][172 * steps + ((cycle - 0) & mask)];
      assert(x1978 != Fp::invalid());
      if (x1978 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1979 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x1979 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x1980 = x6 - x1979;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x1980 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1981 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1981 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1982 = x1981 - x1967;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x1983 = x1982 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1984 = Fp(x1983.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1984);
            reg = x1984;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1985 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x1985 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1986 = x1983 - x1985;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1987 = x1986 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1988 = Fp(x1987.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1988);
            reg = x1988;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x1989 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x1989 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1990 = x1987 - x1989;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1991 = x1990 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x1992 = Fp(x1991.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1992);
            reg = x1992;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x1993 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x1993 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x1994 = x1991 - x1993;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x1995 = x1994 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1995);
          reg = x1995;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x1996 = x7 - x1978;
      if (x1996 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x1997 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x1997 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x1998 = x7 - x1997;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x1999 = x5 - x1997;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2000 = x1998 * x1999;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2000 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2001 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x2001 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2002 = x1967 - x2001;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2002 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2003 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x2003 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2004 = x2003 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2005 = x2004 + x1997;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2006 = x1968 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2007 = x2005 - x2006;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2008 = x2007 + x1969;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2009 = Fp(x2008.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2009);
            reg = x2009;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2010 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2010 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2011 = x2008 - x2010;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2012 = x2011 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2013 = Fp(x2012.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2013);
            reg = x2013;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2014 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2014 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2015 = x2012 - x2014;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2016 = x2015 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2017 = Fp(x2016.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2017);
            reg = x2017;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2018 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2018 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2019 = x2016 - x2018;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2020 = x2019 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2020);
          reg = x2020;
        }
        if (x1999 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2021 = x1912 - x1970;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2021 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2022 = x1913 - x1971;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2022 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2023 = x1914 - x1972;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2023 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2024 = x1915 - x1973;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2024 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2025 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x2025 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x2026 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x2026 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x2027 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x2027 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2028 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x2028 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2029 = args[2][161 * steps + ((cycle - 0) & mask)];
      assert(x2029 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2030 = args[2][162 * steps + ((cycle - 0) & mask)];
      assert(x2030 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2031 = args[2][163 * steps + ((cycle - 0) & mask)];
      assert(x2031 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2032 = args[2][157 * steps + ((cycle - 0) & mask)];
        assert(x2032 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2033 = x2025 - x2032;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2034 = (x2033 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2035 = x7 - x2034;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][173 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2035);
          reg = x2035;
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2036 = args[2][173 * steps + ((cycle - 0) & mask)];
      assert(x2036 != Fp::invalid());
      if (x2036 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2037 = args[2][159 * steps + ((cycle - 0) & mask)];
        assert(x2037 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2038 = x6 - x2037;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2038 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2039 = args[2][157 * steps + ((cycle - 0) & mask)];
        assert(x2039 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2040 = x2039 - x2025;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2041 = x2040 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2042 = Fp(x2041.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2042);
            reg = x2042;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2043 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x2043 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2044 = x2041 - x2043;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2045 = x2044 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2046 = Fp(x2045.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2046);
            reg = x2046;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2047 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x2047 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2048 = x2045 - x2047;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2049 = x2048 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2050 = Fp(x2049.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2050);
            reg = x2050;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2051 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x2051 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2052 = x2049 - x2051;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2053 = x2052 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2053);
          reg = x2053;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2054 = x7 - x2036;
      if (x2054 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2055 = args[2][159 * steps + ((cycle - 0) & mask)];
        assert(x2055 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2056 = x7 - x2055;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2057 = x5 - x2055;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2058 = x2056 * x2057;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2058 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2059 = args[2][157 * steps + ((cycle - 0) & mask)];
        assert(x2059 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2060 = x2025 - x2059;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2060 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2061 = args[2][158 * steps + ((cycle - 0) & mask)];
        assert(x2061 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2062 = x2061 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2063 = x2062 + x2055;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2064 = x2026 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2065 = x2063 - x2064;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2066 = x2065 + x2027;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2067 = Fp(x2066.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2067);
            reg = x2067;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2068 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x2068 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2069 = x2066 - x2068;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2070 = x2069 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2071 = Fp(x2070.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2071);
            reg = x2071;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2072 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x2072 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2073 = x2070 - x2072;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2074 = x2073 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2075 = Fp(x2074.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2075);
            reg = x2075;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2076 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x2076 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2077 = x2074 - x2076;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2078 = x2077 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2078);
          reg = x2078;
        }
        if (x2057 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2079 = x1970 - x2028;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2079 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2080 = x1971 - x2029;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2080 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2081 = x1972 - x2030;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2081 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2082 = x1973 - x2031;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2082 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2083 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x2083 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x2084 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x2084 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x2085 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x2085 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2086 = args[2][167 * steps + ((cycle - 0) & mask)];
      assert(x2086 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2087 = args[2][168 * steps + ((cycle - 0) & mask)];
      assert(x2087 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2088 = args[2][169 * steps + ((cycle - 0) & mask)];
      assert(x2088 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2089 = args[2][170 * steps + ((cycle - 0) & mask)];
      assert(x2089 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2090 = args[2][164 * steps + ((cycle - 0) & mask)];
        assert(x2090 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2091 = x2083 - x2090;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2092 = (x2091 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2093 = x7 - x2092;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][174 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2093);
          reg = x2093;
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkVerifier3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2094 = args[2][174 * steps + ((cycle - 0) & mask)];
      assert(x2094 != Fp::invalid());
      if (x2094 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2095 = args[2][166 * steps + ((cycle - 0) & mask)];
        assert(x2095 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2096 = x6 - x2095;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2096 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2097 = args[2][164 * steps + ((cycle - 0) & mask)];
        assert(x2097 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2098 = x2097 - x2083;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2099 = x2098 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2100 = Fp(x2099.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2100);
            reg = x2100;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2101 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x2101 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2102 = x2099 - x2101;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2103 = x2102 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2104 = Fp(x2103.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2104);
            reg = x2104;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2105 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x2105 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2106 = x2103 - x2105;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2107 = x2106 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2108 = Fp(x2107.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2108);
            reg = x2108;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2109 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x2109 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2110 = x2107 - x2109;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2111 = x2110 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2111);
          reg = x2111;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2112 = x7 - x2094;
      if (x2112 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2113 = args[2][166 * steps + ((cycle - 0) & mask)];
        assert(x2113 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2114 = x7 - x2113;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2115 = x5 - x2113;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2116 = x2114 * x2115;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2116 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2117 = args[2][164 * steps + ((cycle - 0) & mask)];
        assert(x2117 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2118 = x2083 - x2117;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2118 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2119 = args[2][165 * steps + ((cycle - 0) & mask)];
        assert(x2119 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2120 = x2119 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2121 = x2120 + x2113;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2122 = x2084 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2123 = x2121 - x2122;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2124 = x2123 + x2085;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2125 = Fp(x2124.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2125);
            reg = x2125;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2126 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x2126 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2127 = x2124 - x2126;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2128 = x2127 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2129 = Fp(x2128.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2129);
            reg = x2129;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2130 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x2130 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2131 = x2128 - x2130;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2132 = x2131 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2133 = Fp(x2132.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2133);
            reg = x2133;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2134 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x2134 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2135 = x2132 - x2134;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2136 = x2135 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2136);
          reg = x2136;
        }
        if (x2115 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2137 = x2028 - x2086;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2137 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2138 = x2029 - x2087;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2138 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2139 = x2030 - x2088;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2139 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2140 = x2031 - x2089;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2140 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2141 = args[2][164 * steps + ((cycle - 0) & mask)];
      assert(x2141 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x2142 = args[2][165 * steps + ((cycle - 0) & mask)];
      assert(x2142 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x2143 = args[2][166 * steps + ((cycle - 0) & mask)];
      assert(x2143 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2144 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x2144 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2145 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x2145 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2146 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x2146 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2147 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x2147 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2148 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2148 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2149 = x2141 - x2148;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2150 = (x2149 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2151 = x7 - x2150;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][175 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2151);
          reg = x2151;
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkVerifier4/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2152 = args[2][175 * steps + ((cycle - 0) & mask)];
      assert(x2152 != Fp::invalid());
      if (x2152 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2153 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2153 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2154 = x6 - x2153;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2154 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2155 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2155 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2156 = x2155 - x2141;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2157 = x2156 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2158 = Fp(x2157.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][25 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2158);
            reg = x2158;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2159 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x2159 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2160 = x2157 - x2159;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2161 = x2160 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2162 = Fp(x2161.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][26 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2162);
            reg = x2162;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2163 = args[2][26 * steps + ((cycle - 0) & mask)];
        assert(x2163 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2164 = x2161 - x2163;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2165 = x2164 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2166 = Fp(x2165.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][27 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2166);
            reg = x2166;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2167 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x2167 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2168 = x2165 - x2167;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2169 = x2168 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][78 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2169);
          reg = x2169;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2170 = x7 - x2152;
      if (x2170 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2171 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2171 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2172 = x7 - x2171;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2173 = x5 - x2171;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2174 = x2172 * x2173;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2174 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2175 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2175 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2176 = x2141 - x2175;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2176 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2177 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x2177 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2178 = x2177 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2179 = x2178 + x2171;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2180 = x2142 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2181 = x2179 - x2180;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2182 = x2181 + x2143;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2183 = Fp(x2182.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][25 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2183);
            reg = x2183;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2184 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x2184 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2185 = x2182 - x2184;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2186 = x2185 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2187 = Fp(x2186.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][26 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2187);
            reg = x2187;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2188 = args[2][26 * steps + ((cycle - 0) & mask)];
        assert(x2188 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2189 = x2186 - x2188;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2190 = x2189 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2191 = Fp(x2190.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][27 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2191);
            reg = x2191;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2192 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x2192 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2193 = x2190 - x2192;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2194 = x2193 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][78 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2194);
          reg = x2194;
        }
        if (x2173 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2195 = x2086 - x2144;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2195 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2196 = x2087 - x2145;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2196 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2197 = x2088 - x2146;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2197 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2198 = x2089 - x2147;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2198 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x2199 = args[2][99 * steps + ((cycle - 0) & mask)];
    assert(x2199 != Fp::invalid());
    if (x2199 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2200 = host_outs.at(0);
        auto x2201 = host_outs.at(1);
        auto x2202 = host_outs.at(2);
        auto x2203 = host_outs.at(3);
        auto x2204 = host_outs.at(4);
        auto x2205 = host_outs.at(5);
        auto x2206 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2200);
          reg = x2200;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2201);
          reg = x2201;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2202);
          reg = x2202;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2203);
          reg = x2203;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2204);
          reg = x2204;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][141 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2205);
          reg = x2205;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2206);
          reg = x2206;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2207 = host_outs.at(0);
        auto x2208 = host_outs.at(1);
        auto x2209 = host_outs.at(2);
        auto x2210 = host_outs.at(3);
        auto x2211 = host_outs.at(4);
        auto x2212 = host_outs.at(5);
        auto x2213 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2207);
          reg = x2207;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2208);
          reg = x2208;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2209);
          reg = x2209;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2210);
          reg = x2210;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2211);
          reg = x2211;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2212);
          reg = x2212;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2213);
          reg = x2213;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2214 = host_outs.at(0);
        auto x2215 = host_outs.at(1);
        auto x2216 = host_outs.at(2);
        auto x2217 = host_outs.at(3);
        auto x2218 = host_outs.at(4);
        auto x2219 = host_outs.at(5);
        auto x2220 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2214);
          reg = x2214;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2215);
          reg = x2215;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2216);
          reg = x2216;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2217);
          reg = x2217;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2218);
          reg = x2218;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2219);
          reg = x2219;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2220);
          reg = x2220;
        }
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
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2221);
          reg = x2221;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2222);
          reg = x2222;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2223);
          reg = x2223;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2224);
          reg = x2224;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2225);
          reg = x2225;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2226);
          reg = x2226;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2227);
          reg = x2227;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2228 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x2228 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x2229 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x2229 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x2230 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x2230 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2231 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x2231 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2232 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x2232 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2233 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x2233 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2234 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x2234 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2235 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x2235 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2236 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x2236 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2237 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x2237 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2238 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x2238 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2239 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x2239 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2240 = x2228 - x2239;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2241 = (x2240 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2242 = x7 - x2241;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2242);
          reg = x2242;
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2243 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x2243 != Fp::invalid());
      if (x2243 != 0) {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2244 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x2244 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2245 = x6 - x2244;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2245 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2246 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x2246 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2247 = x2246 - x2228;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2248 = x2247 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2249 = Fp(x2248.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2249);
            reg = x2249;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2250 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2250 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2251 = x2248 - x2250;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2252 = x2251 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2253 = Fp(x2252.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2253);
            reg = x2253;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2254 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2254 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2255 = x2252 - x2254;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2256 = x2255 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2257 = Fp(x2256.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2257);
            reg = x2257;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2258 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2258 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2259 = x2256 - x2258;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2260 = x2259 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2260);
          reg = x2260;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2261 = x7 - x2243;
      if (x2261 != 0) {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2262 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x2262 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2263 = x7 - x2262;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2264 = x5 - x2262;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2265 = x2263 * x2264;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2265 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2266 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x2266 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2267 = x2228 - x2266;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2267 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2268 = args[2][137 * steps + ((cycle - 0) & mask)];
        assert(x2268 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2269 = x2268 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2270 = x2269 + x2262;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2271 = x2229 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2272 = x2270 - x2271;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2273 = x2272 + x2230;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2274 = Fp(x2273.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2274);
            reg = x2274;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2275 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2275 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2276 = x2273 - x2275;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2277 = x2276 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2278 = Fp(x2277.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2278);
            reg = x2278;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2279 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2279 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2280 = x2277 - x2279;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2281 = x2280 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2282 = Fp(x2281.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2282);
            reg = x2282;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2283 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2283 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2284 = x2281 - x2283;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2285 = x2284 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2285);
          reg = x2285;
        }
        if (x2264 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2286 = x2231 - x2235;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2286 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2287 = x2232 - x2236;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2287 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2288 = x2233 - x2237;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2288 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2289 = x2234 - x2238;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2289 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2290 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x2290 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x2291 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x2291 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x2292 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x2292 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2293 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x2293 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2294 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x2294 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2295 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x2295 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2296 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x2296 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2297 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x2297 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2298 = x2290 - x2297;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2299 = (x2298 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2300 = x7 - x2299;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2300);
          reg = x2300;
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2301 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x2301 != Fp::invalid());
      if (x2301 != 0) {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2302 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x2302 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2303 = x6 - x2302;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2303 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2304 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x2304 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2305 = x2304 - x2290;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2306 = x2305 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2307 = Fp(x2306.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2307);
            reg = x2307;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2308 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2308 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2309 = x2306 - x2308;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2310 = x2309 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2311 = Fp(x2310.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2311);
            reg = x2311;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2312 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2312 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2313 = x2310 - x2312;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2314 = x2313 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2315 = Fp(x2314.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2315);
            reg = x2315;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2316 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2316 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2317 = x2314 - x2316;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2318 = x2317 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2318);
          reg = x2318;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2319 = x7 - x2301;
      if (x2319 != 0) {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2320 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x2320 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2321 = x7 - x2320;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2322 = x5 - x2320;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2323 = x2321 * x2322;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2323 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2324 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x2324 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2325 = x2290 - x2324;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2325 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2326 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x2326 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2327 = x2326 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2328 = x2327 + x2320;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2329 = x2291 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2330 = x2328 - x2329;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2331 = x2330 + x2292;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2332 = Fp(x2331.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2332);
            reg = x2332;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2333 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2333 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2334 = x2331 - x2333;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2335 = x2334 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2336 = Fp(x2335.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2336);
            reg = x2336;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2337 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2337 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2338 = x2335 - x2337;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2339 = x2338 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2340 = Fp(x2339.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2340);
            reg = x2340;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2341 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2341 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2342 = x2339 - x2341;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2343 = x2342 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2343);
          reg = x2343;
        }
        if (x2322 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2344 = x2235 - x2293;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2344 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2345 = x2236 - x2294;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2345 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2346 = x2237 - x2295;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2346 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2347 = x2238 - x2296;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2347 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2348 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x2348 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x2349 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x2349 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x2350 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x2350 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2351 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x2351 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2352 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x2352 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2353 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x2353 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2354 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x2354 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2355 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x2355 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2356 = x2348 - x2355;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2357 = (x2356 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2358 = x7 - x2357;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2358);
          reg = x2358;
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2359 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x2359 != Fp::invalid());
      if (x2359 != 0) {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2360 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x2360 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2361 = x6 - x2360;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2361 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2362 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x2362 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2363 = x2362 - x2348;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2364 = x2363 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2365 = Fp(x2364.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2365);
            reg = x2365;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2366 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x2366 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2367 = x2364 - x2366;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2368 = x2367 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2369 = Fp(x2368.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2369);
            reg = x2369;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2370 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x2370 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2371 = x2368 - x2370;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2372 = x2371 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2373 = Fp(x2372.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2373);
            reg = x2373;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2374 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x2374 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2375 = x2372 - x2374;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2376 = x2375 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2376);
          reg = x2376;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2377 = x7 - x2359;
      if (x2377 != 0) {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2378 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x2378 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2379 = x7 - x2378;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2380 = x5 - x2378;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2381 = x2379 * x2380;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2381 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2382 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x2382 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2383 = x2348 - x2382;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2383 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2384 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x2384 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2385 = x2384 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2386 = x2385 + x2378;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2387 = x2349 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2388 = x2386 - x2387;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2389 = x2388 + x2350;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2390 = Fp(x2389.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2390);
            reg = x2390;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2391 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x2391 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2392 = x2389 - x2391;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2393 = x2392 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2394 = Fp(x2393.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2394);
            reg = x2394;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2395 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x2395 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2396 = x2393 - x2395;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2397 = x2396 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2398 = Fp(x2397.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2398);
            reg = x2398;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2399 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x2399 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2400 = x2397 - x2399;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2401 = x2400 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2401);
          reg = x2401;
        }
        if (x2380 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2402 = x2293 - x2351;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2402 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2403 = x2294 - x2352;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2403 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2404 = x2295 - x2353;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2404 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2405 = x2296 - x2354;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2405 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2406 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x2406 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x2407 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x2407 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x2408 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x2408 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2409 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x2409 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2410 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x2410 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2411 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x2411 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2412 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x2412 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2413 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2413 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2414 = x2406 - x2413;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2415 = (x2414 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2416 = x7 - x2415;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2416);
          reg = x2416;
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkVerifier3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2417 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x2417 != Fp::invalid());
      if (x2417 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2418 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2418 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2419 = x6 - x2418;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2419 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2420 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2420 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2421 = x2420 - x2406;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2422 = x2421 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2423 = Fp(x2422.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2423);
            reg = x2423;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2424 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x2424 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2425 = x2422 - x2424;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2426 = x2425 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2427 = Fp(x2426.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2427);
            reg = x2427;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2428 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x2428 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2429 = x2426 - x2428;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2430 = x2429 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2431 = Fp(x2430.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2431);
            reg = x2431;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2432 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x2432 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2433 = x2430 - x2432;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2434 = x2433 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2434);
          reg = x2434;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2435 = x7 - x2417;
      if (x2435 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2436 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2436 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2437 = x7 - x2436;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2438 = x5 - x2436;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2439 = x2437 * x2438;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2439 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2440 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2440 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2441 = x2406 - x2440;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2441 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2442 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x2442 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2443 = x2442 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2444 = x2443 + x2436;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2445 = x2407 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2446 = x2444 - x2445;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2447 = x2446 + x2408;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2448 = Fp(x2447.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2448);
            reg = x2448;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2449 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x2449 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2450 = x2447 - x2449;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2451 = x2450 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2452 = Fp(x2451.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2452);
            reg = x2452;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2453 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x2453 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2454 = x2451 - x2453;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2455 = x2454 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2456 = Fp(x2455.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2456);
            reg = x2456;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2457 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x2457 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2458 = x2455 - x2457;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2459 = x2458 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2459);
          reg = x2459;
        }
        if (x2438 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2460 = x2351 - x2409;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2460 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2461 = x2352 - x2410;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2461 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2462 = x2353 - x2411;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2462 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2463 = x2354 - x2412;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2463 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x2464 = args[2][100 * steps + ((cycle - 0) & mask)];
    assert(x2464 != Fp::invalid());
    if (x2464 != 0) {
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2465 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x2465 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2466 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x2466 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2467 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x2467 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2468 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x2468 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2469 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x2469 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2470 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x2470 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2471 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x2471 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2465);
        reg = x2465;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2466);
        reg = x2466;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2467);
        reg = x2467;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2468);
        reg = x2468;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2469);
        reg = x2469;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2470);
        reg = x2470;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2471);
        reg = x2471;
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x2472 = args[2][101 * steps + ((cycle - 0) & mask)];
    assert(x2472 != Fp::invalid());
    if (x2472 != 0) {
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2473 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x2473 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2474 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x2474 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2475 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x2475 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2476 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x2476 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2477 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x2477 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2478 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x2478 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2479 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x2479 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":36:3)
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2473);
        reg = x2473;
      }
      // loc("cirgen/components/ram.cpp":37:3)
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2474);
        reg = x2474;
      }
      // loc("cirgen/components/ram.cpp":38:3)
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2475);
        reg = x2475;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2476);
        reg = x2476;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2477);
        reg = x2477;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2478);
        reg = x2478;
      }
      // loc("cirgen/components/u32.cpp":82:5)
      {
        auto& reg = args[2][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2479);
        reg = x2479;
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x2480 = args[2][102 * steps + ((cycle - 0) & mask)];
    assert(x2480 != Fp::invalid());
    if (x2480 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2481 = host_outs.at(0);
        auto x2482 = host_outs.at(1);
        auto x2483 = host_outs.at(2);
        auto x2484 = host_outs.at(3);
        auto x2485 = host_outs.at(4);
        auto x2486 = host_outs.at(5);
        auto x2487 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2481);
          reg = x2481;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2482);
          reg = x2482;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2483);
          reg = x2483;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2484);
          reg = x2484;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2485);
          reg = x2485;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2486);
          reg = x2486;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2487);
          reg = x2487;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2488 = host_outs.at(0);
        auto x2489 = host_outs.at(1);
        auto x2490 = host_outs.at(2);
        auto x2491 = host_outs.at(3);
        auto x2492 = host_outs.at(4);
        auto x2493 = host_outs.at(5);
        auto x2494 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2488);
          reg = x2488;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2489);
          reg = x2489;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2490);
          reg = x2490;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2491);
          reg = x2491;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2492);
          reg = x2492;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2493);
          reg = x2493;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2494);
          reg = x2494;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2495 = host_outs.at(0);
        auto x2496 = host_outs.at(1);
        auto x2497 = host_outs.at(2);
        auto x2498 = host_outs.at(3);
        auto x2499 = host_outs.at(4);
        auto x2500 = host_outs.at(5);
        auto x2501 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2495);
          reg = x2495;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2496);
          reg = x2496;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2497);
          reg = x2497;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2498);
          reg = x2498;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][161 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2499);
          reg = x2499;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][162 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2500);
          reg = x2500;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][163 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2501);
          reg = x2501;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2502 = host_outs.at(0);
        auto x2503 = host_outs.at(1);
        auto x2504 = host_outs.at(2);
        auto x2505 = host_outs.at(3);
        auto x2506 = host_outs.at(4);
        auto x2507 = host_outs.at(5);
        auto x2508 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][164 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2502);
          reg = x2502;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][165 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2503);
          reg = x2503;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][166 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2504);
          reg = x2504;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][167 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2505);
          reg = x2505;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2506);
          reg = x2506;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][169 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2507);
          reg = x2507;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2508);
          reg = x2508;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2509 = host_outs.at(0);
        auto x2510 = host_outs.at(1);
        auto x2511 = host_outs.at(2);
        auto x2512 = host_outs.at(3);
        auto x2513 = host_outs.at(4);
        auto x2514 = host_outs.at(5);
        auto x2515 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2509);
          reg = x2509;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2510);
          reg = x2510;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2511);
          reg = x2511;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2512);
          reg = x2512;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2513);
          reg = x2513;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2514);
          reg = x2514;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2515);
          reg = x2515;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2516 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x2516 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x2517 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x2517 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x2518 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x2518 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2519 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x2519 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2520 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x2520 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2521 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x2521 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2522 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x2522 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2523 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x2523 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2524 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x2524 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2525 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x2525 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2526 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x2526 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2527 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x2527 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2528 = x2516 - x2527;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2529 = (x2528 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2530 = x7 - x2529;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][171 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2530);
          reg = x2530;
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2531 = args[2][171 * steps + ((cycle - 0) & mask)];
      assert(x2531 != Fp::invalid());
      if (x2531 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2532 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x2532 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2533 = x6 - x2532;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2533 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2534 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x2534 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2535 = x2534 - x2516;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2536 = x2535 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2537 = Fp(x2536.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2537);
            reg = x2537;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2538 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2538 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2539 = x2536 - x2538;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2540 = x2539 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2541 = Fp(x2540.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2541);
            reg = x2541;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2542 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2542 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2543 = x2540 - x2542;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2544 = x2543 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2545 = Fp(x2544.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2545);
            reg = x2545;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2546 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2546 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2547 = x2544 - x2546;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2548 = x2547 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2548);
          reg = x2548;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2549 = x7 - x2531;
      if (x2549 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2550 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x2550 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2551 = x7 - x2550;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2552 = x5 - x2550;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2553 = x2551 * x2552;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2553 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2554 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x2554 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2555 = x2516 - x2554;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2555 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2556 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x2556 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2557 = x2556 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2558 = x2557 + x2550;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2559 = x2517 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2560 = x2558 - x2559;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2561 = x2560 + x2518;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2562 = Fp(x2561.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2562);
            reg = x2562;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2563 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2563 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2564 = x2561 - x2563;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2565 = x2564 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2566 = Fp(x2565.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2566);
            reg = x2566;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2567 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2567 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2568 = x2565 - x2567;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2569 = x2568 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2570 = Fp(x2569.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2570);
            reg = x2570;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2571 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2571 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2572 = x2569 - x2571;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2573 = x2572 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2573);
          reg = x2573;
        }
        if (x2552 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2574 = x2519 - x2523;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2574 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2575 = x2520 - x2524;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2575 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2576 = x2521 - x2525;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2576 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2577 = x2522 - x2526;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2577 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2578 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x2578 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x2579 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x2579 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x2580 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x2580 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2581 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x2581 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2582 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x2582 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2583 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x2583 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2584 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x2584 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2585 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x2585 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2586 = x2578 - x2585;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2587 = (x2586 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2588 = x7 - x2587;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2588);
          reg = x2588;
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2589 = args[2][172 * steps + ((cycle - 0) & mask)];
      assert(x2589 != Fp::invalid());
      if (x2589 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2590 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x2590 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2591 = x6 - x2590;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2591 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2592 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x2592 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2593 = x2592 - x2578;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2594 = x2593 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2595 = Fp(x2594.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2595);
            reg = x2595;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2596 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2596 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2597 = x2594 - x2596;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2598 = x2597 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2599 = Fp(x2598.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2599);
            reg = x2599;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2600 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2600 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2601 = x2598 - x2600;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2602 = x2601 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2603 = Fp(x2602.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2603);
            reg = x2603;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2604 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2604 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2605 = x2602 - x2604;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2606 = x2605 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2606);
          reg = x2606;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2607 = x7 - x2589;
      if (x2607 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2608 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x2608 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2609 = x7 - x2608;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2610 = x5 - x2608;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2611 = x2609 * x2610;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2611 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2612 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x2612 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2613 = x2578 - x2612;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2613 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2614 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x2614 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2615 = x2614 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2616 = x2615 + x2608;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2617 = x2579 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2618 = x2616 - x2617;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2619 = x2618 + x2580;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2620 = Fp(x2619.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2620);
            reg = x2620;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2621 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2621 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2622 = x2619 - x2621;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2623 = x2622 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2624 = Fp(x2623.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2624);
            reg = x2624;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2625 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2625 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2626 = x2623 - x2625;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2627 = x2626 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2628 = Fp(x2627.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2628);
            reg = x2628;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2629 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2629 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2630 = x2627 - x2629;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2631 = x2630 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2631);
          reg = x2631;
        }
        if (x2610 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2632 = x2523 - x2581;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2632 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2633 = x2524 - x2582;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2633 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2634 = x2525 - x2583;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2634 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2635 = x2526 - x2584;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2635 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2636 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x2636 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x2637 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x2637 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x2638 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x2638 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2639 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x2639 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2640 = args[2][161 * steps + ((cycle - 0) & mask)];
      assert(x2640 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2641 = args[2][162 * steps + ((cycle - 0) & mask)];
      assert(x2641 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2642 = args[2][163 * steps + ((cycle - 0) & mask)];
      assert(x2642 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2643 = args[2][157 * steps + ((cycle - 0) & mask)];
        assert(x2643 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2644 = x2636 - x2643;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2645 = (x2644 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2646 = x7 - x2645;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][173 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2646);
          reg = x2646;
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2647 = args[2][173 * steps + ((cycle - 0) & mask)];
      assert(x2647 != Fp::invalid());
      if (x2647 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2648 = args[2][159 * steps + ((cycle - 0) & mask)];
        assert(x2648 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2649 = x6 - x2648;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2649 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2650 = args[2][157 * steps + ((cycle - 0) & mask)];
        assert(x2650 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2651 = x2650 - x2636;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2652 = x2651 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2653 = Fp(x2652.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2653);
            reg = x2653;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2654 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x2654 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2655 = x2652 - x2654;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2656 = x2655 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2657 = Fp(x2656.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2657);
            reg = x2657;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2658 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x2658 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2659 = x2656 - x2658;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2660 = x2659 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2661 = Fp(x2660.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2661);
            reg = x2661;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2662 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x2662 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2663 = x2660 - x2662;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2664 = x2663 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2664);
          reg = x2664;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2665 = x7 - x2647;
      if (x2665 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2666 = args[2][159 * steps + ((cycle - 0) & mask)];
        assert(x2666 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2667 = x7 - x2666;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2668 = x5 - x2666;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2669 = x2667 * x2668;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2669 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2670 = args[2][157 * steps + ((cycle - 0) & mask)];
        assert(x2670 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2671 = x2636 - x2670;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2671 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2672 = args[2][158 * steps + ((cycle - 0) & mask)];
        assert(x2672 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2673 = x2672 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2674 = x2673 + x2666;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2675 = x2637 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2676 = x2674 - x2675;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2677 = x2676 + x2638;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2678 = Fp(x2677.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2678);
            reg = x2678;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2679 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x2679 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2680 = x2677 - x2679;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2681 = x2680 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2682 = Fp(x2681.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2682);
            reg = x2682;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2683 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x2683 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2684 = x2681 - x2683;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2685 = x2684 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2686 = Fp(x2685.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2686);
            reg = x2686;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2687 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x2687 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2688 = x2685 - x2687;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2689 = x2688 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2689);
          reg = x2689;
        }
        if (x2668 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2690 = x2581 - x2639;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2690 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2691 = x2582 - x2640;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2691 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2692 = x2583 - x2641;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2692 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2693 = x2584 - x2642;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2693 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2694 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x2694 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x2695 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x2695 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x2696 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x2696 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2697 = args[2][167 * steps + ((cycle - 0) & mask)];
      assert(x2697 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2698 = args[2][168 * steps + ((cycle - 0) & mask)];
      assert(x2698 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2699 = args[2][169 * steps + ((cycle - 0) & mask)];
      assert(x2699 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2700 = args[2][170 * steps + ((cycle - 0) & mask)];
      assert(x2700 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2701 = args[2][164 * steps + ((cycle - 0) & mask)];
        assert(x2701 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2702 = x2694 - x2701;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2703 = (x2702 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2704 = x7 - x2703;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][174 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2704);
          reg = x2704;
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkVerifier3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2705 = args[2][174 * steps + ((cycle - 0) & mask)];
      assert(x2705 != Fp::invalid());
      if (x2705 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2706 = args[2][166 * steps + ((cycle - 0) & mask)];
        assert(x2706 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2707 = x6 - x2706;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2707 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2708 = args[2][164 * steps + ((cycle - 0) & mask)];
        assert(x2708 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2709 = x2708 - x2694;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2710 = x2709 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2711 = Fp(x2710.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2711);
            reg = x2711;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2712 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x2712 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2713 = x2710 - x2712;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2714 = x2713 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2715 = Fp(x2714.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2715);
            reg = x2715;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2716 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x2716 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2717 = x2714 - x2716;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2718 = x2717 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2719 = Fp(x2718.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2719);
            reg = x2719;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2720 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x2720 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2721 = x2718 - x2720;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2722 = x2721 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2722);
          reg = x2722;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2723 = x7 - x2705;
      if (x2723 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2724 = args[2][166 * steps + ((cycle - 0) & mask)];
        assert(x2724 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2725 = x7 - x2724;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2726 = x5 - x2724;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2727 = x2725 * x2726;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2727 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2728 = args[2][164 * steps + ((cycle - 0) & mask)];
        assert(x2728 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2729 = x2694 - x2728;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2729 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2730 = args[2][165 * steps + ((cycle - 0) & mask)];
        assert(x2730 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2731 = x2730 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2732 = x2731 + x2724;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2733 = x2695 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2734 = x2732 - x2733;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2735 = x2734 + x2696;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2736 = Fp(x2735.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2736);
            reg = x2736;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2737 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x2737 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2738 = x2735 - x2737;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2739 = x2738 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2740 = Fp(x2739.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2740);
            reg = x2740;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2741 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x2741 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2742 = x2739 - x2741;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2743 = x2742 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2744 = Fp(x2743.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2744);
            reg = x2744;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2745 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x2745 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2746 = x2743 - x2745;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2747 = x2746 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2747);
          reg = x2747;
        }
        if (x2726 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2748 = x2639 - x2697;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2748 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2749 = x2640 - x2698;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2749 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2750 = x2641 - x2699;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2750 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2751 = x2642 - x2700;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2751 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2752 = args[2][164 * steps + ((cycle - 0) & mask)];
      assert(x2752 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x2753 = args[2][165 * steps + ((cycle - 0) & mask)];
      assert(x2753 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x2754 = args[2][166 * steps + ((cycle - 0) & mask)];
      assert(x2754 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2755 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x2755 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2756 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x2756 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2757 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x2757 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2758 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x2758 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2759 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2759 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2760 = x2752 - x2759;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2761 = (x2760 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2762 = x7 - x2761;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][175 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2762);
          reg = x2762;
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkVerifier4/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2763 = args[2][175 * steps + ((cycle - 0) & mask)];
      assert(x2763 != Fp::invalid());
      if (x2763 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2764 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2764 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2765 = x6 - x2764;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2765 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2766 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2766 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2767 = x2766 - x2752;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2768 = x2767 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2769 = Fp(x2768.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][25 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2769);
            reg = x2769;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2770 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x2770 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2771 = x2768 - x2770;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2772 = x2771 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2773 = Fp(x2772.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][26 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2773);
            reg = x2773;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2774 = args[2][26 * steps + ((cycle - 0) & mask)];
        assert(x2774 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2775 = x2772 - x2774;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2776 = x2775 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2777 = Fp(x2776.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][27 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2777);
            reg = x2777;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2778 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x2778 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2779 = x2776 - x2778;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2780 = x2779 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][78 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2780);
          reg = x2780;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2781 = x7 - x2763;
      if (x2781 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2782 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2782 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2783 = x7 - x2782;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2784 = x5 - x2782;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2785 = x2783 * x2784;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2785 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2786 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2786 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2787 = x2752 - x2786;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2787 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2788 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x2788 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2789 = x2788 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2790 = x2789 + x2782;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2791 = x2753 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2792 = x2790 - x2791;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2793 = x2792 + x2754;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2794 = Fp(x2793.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][25 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2794);
            reg = x2794;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2795 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x2795 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2796 = x2793 - x2795;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2797 = x2796 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2798 = Fp(x2797.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][26 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2798);
            reg = x2798;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2799 = args[2][26 * steps + ((cycle - 0) & mask)];
        assert(x2799 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2800 = x2797 - x2799;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2801 = x2800 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2802 = Fp(x2801.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][27 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2802);
            reg = x2802;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2803 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x2803 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2804 = x2801 - x2803;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2805 = x2804 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][78 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2805);
          reg = x2805;
        }
        if (x2784 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2806 = x2697 - x2755;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2806 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2807 = x2698 - x2756;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2807 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2808 = x2699 - x2757;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2808 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2809 = x2700 - x2758;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2809 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x2810 = args[2][103 * steps + ((cycle - 0) & mask)];
    assert(x2810 != Fp::invalid());
    if (x2810 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2811 = host_outs.at(0);
        auto x2812 = host_outs.at(1);
        auto x2813 = host_outs.at(2);
        auto x2814 = host_outs.at(3);
        auto x2815 = host_outs.at(4);
        auto x2816 = host_outs.at(5);
        auto x2817 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][122 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2811);
          reg = x2811;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][123 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2812);
          reg = x2812;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][124 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2813);
          reg = x2813;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][125 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2814);
          reg = x2814;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][126 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2815);
          reg = x2815;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][127 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2816);
          reg = x2816;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][128 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2817);
          reg = x2817;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2818 = host_outs.at(0);
        auto x2819 = host_outs.at(1);
        auto x2820 = host_outs.at(2);
        auto x2821 = host_outs.at(3);
        auto x2822 = host_outs.at(4);
        auto x2823 = host_outs.at(5);
        auto x2824 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2818);
          reg = x2818;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2819);
          reg = x2819;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2820);
          reg = x2820;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2821);
          reg = x2821;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2822);
          reg = x2822;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2823);
          reg = x2823;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2824);
          reg = x2824;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2825 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x2825 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x2826 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x2826 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x2827 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x2827 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2828 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x2828 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2829 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x2829 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2830 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x2830 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2831 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x2831 != Fp::invalid());
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2832 = args[2][125 * steps + ((cycle - 0) & mask)];
      assert(x2832 != Fp::invalid());
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2833 = args[2][126 * steps + ((cycle - 0) & mask)];
      assert(x2833 != Fp::invalid());
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2834 = args[2][127 * steps + ((cycle - 0) & mask)];
      assert(x2834 != Fp::invalid());
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2835 = args[2][128 * steps + ((cycle - 0) & mask)];
      assert(x2835 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2836 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x2836 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2837 = x2825 - x2836;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2838 = (x2837 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2839 = x7 - x2838;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][129 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2839);
          reg = x2839;
        }
      }
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2840 = args[2][129 * steps + ((cycle - 0) & mask)];
      assert(x2840 != Fp::invalid());
      if (x2840 != 0) {
        // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2841 = args[2][124 * steps + ((cycle - 0) & mask)];
        assert(x2841 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2842 = x6 - x2841;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2842 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2843 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x2843 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2844 = x2843 - x2825;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2845 = x2844 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2846 = Fp(x2845.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2846);
            reg = x2846;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2847 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2847 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2848 = x2845 - x2847;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2849 = x2848 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2850 = Fp(x2849.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2850);
            reg = x2850;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2851 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2851 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2852 = x2849 - x2851;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2853 = x2852 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2854 = Fp(x2853.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2854);
            reg = x2854;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2855 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2855 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2856 = x2853 - x2855;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2857 = x2856 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2857);
          reg = x2857;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2858 = x7 - x2840;
      if (x2858 != 0) {
        // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2859 = args[2][124 * steps + ((cycle - 0) & mask)];
        assert(x2859 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2860 = x7 - x2859;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2861 = x5 - x2859;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2862 = x2860 * x2861;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2862 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2863 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x2863 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2864 = x2825 - x2863;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2864 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2865 = args[2][123 * steps + ((cycle - 0) & mask)];
        assert(x2865 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2866 = x2865 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2867 = x2866 + x2859;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2868 = x2826 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2869 = x2867 - x2868;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2870 = x2869 + x2827;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2871 = Fp(x2870.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2871);
            reg = x2871;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2872 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2872 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2873 = x2870 - x2872;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2874 = x2873 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2875 = Fp(x2874.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2875);
            reg = x2875;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2876 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2876 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2877 = x2874 - x2876;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2878 = x2877 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2879 = Fp(x2878.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2879);
            reg = x2879;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2880 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2880 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2881 = x2878 - x2880;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2882 = x2881 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2882);
          reg = x2882;
        }
        if (x2861 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2883 = x2828 - x2832;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2883 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2884 = x2829 - x2833;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2884 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2885 = x2830 - x2834;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2885 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2886 = x2831 - x2835;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2886 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2887 = args[2][122 * steps + ((cycle - 0) & mask)];
      assert(x2887 != Fp::invalid());
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x2888 = args[2][123 * steps + ((cycle - 0) & mask)];
      assert(x2888 != Fp::invalid());
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x2889 = args[2][124 * steps + ((cycle - 0) & mask)];
      assert(x2889 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2890 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x2890 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2891 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x2891 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2892 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x2892 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2893 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x2893 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2894 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2894 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2895 = x2887 - x2894;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2896 = (x2895 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2897 = x7 - x2896;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][130 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2897);
          reg = x2897;
        }
      }
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2898 = args[2][130 * steps + ((cycle - 0) & mask)];
      assert(x2898 != Fp::invalid());
      if (x2898 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2899 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2899 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2900 = x6 - x2899;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2900 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2901 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2901 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2902 = x2901 - x2887;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2903 = x2902 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2904 = Fp(x2903.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2904);
            reg = x2904;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2905 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2905 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2906 = x2903 - x2905;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2907 = x2906 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2908 = Fp(x2907.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2908);
            reg = x2908;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2909 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2909 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2910 = x2907 - x2909;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2911 = x2910 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2912 = Fp(x2911.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2912);
            reg = x2912;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2913 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2913 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2914 = x2911 - x2913;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2915 = x2914 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2915);
          reg = x2915;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2916 = x7 - x2898;
      if (x2916 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2917 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2917 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2918 = x7 - x2917;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2919 = x5 - x2917;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2920 = x2918 * x2919;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2920 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2921 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2921 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2922 = x2887 - x2921;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2922 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2923 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x2923 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2924 = x2923 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2925 = x2924 + x2917;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x2926 = x2888 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2927 = x2925 - x2926;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x2928 = x2927 + x2889;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2929 = Fp(x2928.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2929);
            reg = x2929;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2930 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2930 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2931 = x2928 - x2930;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2932 = x2931 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2933 = Fp(x2932.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2933);
            reg = x2933;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2934 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2934 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2935 = x2932 - x2934;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2936 = x2935 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2937 = Fp(x2936.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2937);
            reg = x2937;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2938 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2938 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2939 = x2936 - x2938;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2940 = x2939 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2940);
          reg = x2940;
        }
        if (x2919 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2941 = x2832 - x2890;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2941 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2942 = x2833 - x2891;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2942 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2943 = x2834 - x2892;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2943 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x2944 = x2835 - x2893;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x2944 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x2945 = args[2][104 * steps + ((cycle - 0) & mask)];
    assert(x2945 != Fp::invalid());
    if (x2945 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2946 = host_outs.at(0);
        auto x2947 = host_outs.at(1);
        auto x2948 = host_outs.at(2);
        auto x2949 = host_outs.at(3);
        auto x2950 = host_outs.at(4);
        auto x2951 = host_outs.at(5);
        auto x2952 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][122 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2946);
          reg = x2946;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][123 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2947);
          reg = x2947;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][124 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2948);
          reg = x2948;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][125 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2949);
          reg = x2949;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][126 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2950);
          reg = x2950;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][127 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2951);
          reg = x2951;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][128 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2952);
          reg = x2952;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2953 = host_outs.at(0);
        auto x2954 = host_outs.at(1);
        auto x2955 = host_outs.at(2);
        auto x2956 = host_outs.at(3);
        auto x2957 = host_outs.at(4);
        auto x2958 = host_outs.at(5);
        auto x2959 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2953);
          reg = x2953;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2954);
          reg = x2954;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2955);
          reg = x2955;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2956);
          reg = x2956;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2957);
          reg = x2957;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2958);
          reg = x2958;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2959);
          reg = x2959;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x2960 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x2960 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x2961 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x2961 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x2962 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x2962 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2963 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x2963 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2964 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x2964 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2965 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x2965 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2966 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x2966 != Fp::invalid());
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2967 = args[2][125 * steps + ((cycle - 0) & mask)];
      assert(x2967 != Fp::invalid());
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2968 = args[2][126 * steps + ((cycle - 0) & mask)];
      assert(x2968 != Fp::invalid());
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2969 = args[2][127 * steps + ((cycle - 0) & mask)];
      assert(x2969 != Fp::invalid());
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2970 = args[2][128 * steps + ((cycle - 0) & mask)];
      assert(x2970 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2971 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x2971 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2972 = x2960 - x2971;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x2973 = (x2972 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x2974 = x7 - x2973;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][129 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2974);
          reg = x2974;
        }
      }
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x2975 = args[2][129 * steps + ((cycle - 0) & mask)];
      assert(x2975 != Fp::invalid());
      if (x2975 != 0) {
        // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2976 = args[2][124 * steps + ((cycle - 0) & mask)];
        assert(x2976 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x2977 = x6 - x2976;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x2977 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2978 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x2978 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2979 = x2978 - x2960;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x2980 = x2979 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2981 = Fp(x2980.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2981);
            reg = x2981;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2982 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2982 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2983 = x2980 - x2982;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2984 = x2983 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2985 = Fp(x2984.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2985);
            reg = x2985;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x2986 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2986 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2987 = x2984 - x2986;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2988 = x2987 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x2989 = Fp(x2988.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2989);
            reg = x2989;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x2990 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2990 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x2991 = x2988 - x2990;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x2992 = x2991 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2992);
          reg = x2992;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x2993 = x7 - x2975;
      if (x2993 != 0) {
        // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2994 = args[2][124 * steps + ((cycle - 0) & mask)];
        assert(x2994 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x2995 = x7 - x2994;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x2996 = x5 - x2994;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x2997 = x2995 * x2996;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x2997 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x2998 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x2998 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x2999 = x2960 - x2998;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x2999 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3000 = args[2][123 * steps + ((cycle - 0) & mask)];
        assert(x3000 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3001 = x3000 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3002 = x3001 + x2994;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3003 = x2961 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3004 = x3002 - x3003;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3005 = x3004 + x2962;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3006 = Fp(x3005.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3006);
            reg = x3006;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3007 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x3007 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3008 = x3005 - x3007;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3009 = x3008 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3010 = Fp(x3009.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3010);
            reg = x3010;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3011 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x3011 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3012 = x3009 - x3011;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3013 = x3012 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3014 = Fp(x3013.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3014);
            reg = x3014;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3015 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x3015 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3016 = x3013 - x3015;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3017 = x3016 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3017);
          reg = x3017;
        }
        if (x2996 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3018 = x2963 - x2967;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3018 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3019 = x2964 - x2968;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3019 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3020 = x2965 - x2969;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3020 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3021 = x2966 - x2970;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3021 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("cirgen/components/ram.cpp":51:40))
      auto x3022 = args[2][122 * steps + ((cycle - 0) & mask)];
      assert(x3022 != Fp::invalid());
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x3023 = args[2][123 * steps + ((cycle - 0) & mask)];
      assert(x3023 != Fp::invalid());
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x3024 = args[2][124 * steps + ((cycle - 0) & mask)];
      assert(x3024 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3025 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x3025 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3026 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x3026 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3027 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x3027 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3028 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x3028 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3029 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x3029 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3030 = x3022 - x3029;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3031 = (x3030 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x3032 = x7 - x3031;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][130 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3032);
          reg = x3032;
        }
      }
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3033 = args[2][130 * steps + ((cycle - 0) & mask)];
      assert(x3033 != Fp::invalid());
      if (x3033 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3034 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x3034 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x3035 = x6 - x3034;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x3035 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3036 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x3036 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3037 = x3036 - x3022;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3038 = x3037 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3039 = Fp(x3038.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3039);
            reg = x3039;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3040 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x3040 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3041 = x3038 - x3040;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3042 = x3041 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3043 = Fp(x3042.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3043);
            reg = x3043;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3044 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x3044 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3045 = x3042 - x3044;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3046 = x3045 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3047 = Fp(x3046.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3047);
            reg = x3047;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3048 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x3048 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3049 = x3046 - x3048;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3050 = x3049 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3050);
          reg = x3050;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x3051 = x7 - x3033;
      if (x3051 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3052 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x3052 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x3053 = x7 - x3052;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x3054 = x5 - x3052;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x3055 = x3053 * x3054;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x3055 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3056 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x3056 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x3057 = x3022 - x3056;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x3057 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3058 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x3058 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3059 = x3058 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3060 = x3059 + x3052;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3061 = x3023 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3062 = x3060 - x3061;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3063 = x3062 + x3024;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3064 = Fp(x3063.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3064);
            reg = x3064;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3065 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x3065 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3066 = x3063 - x3065;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3067 = x3066 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3068 = Fp(x3067.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3068);
            reg = x3068;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3069 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x3069 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3070 = x3067 - x3069;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3071 = x3070 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3072 = Fp(x3071.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3072);
            reg = x3072;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3073 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x3073 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3074 = x3071 - x3073;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3075 = x3074 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3075);
          reg = x3075;
        }
        if (x3054 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3076 = x2967 - x3025;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3076 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3077 = x2968 - x3026;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3077 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3078 = x2969 - x3027;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3078 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3079 = x2970 - x3028;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3079 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x3080 = args[2][105 * steps + ((cycle - 0) & mask)];
    assert(x3080 != Fp::invalid());
    if (x3080 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x3081 = host_outs.at(0);
        auto x3082 = host_outs.at(1);
        auto x3083 = host_outs.at(2);
        auto x3084 = host_outs.at(3);
        auto x3085 = host_outs.at(4);
        auto x3086 = host_outs.at(5);
        auto x3087 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][122 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3081);
          reg = x3081;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][123 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3082);
          reg = x3082;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][124 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3083);
          reg = x3083;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][125 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3084);
          reg = x3084;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][126 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3085);
          reg = x3085;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][127 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3086);
          reg = x3086;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][128 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3087);
          reg = x3087;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x3088 = host_outs.at(0);
        auto x3089 = host_outs.at(1);
        auto x3090 = host_outs.at(2);
        auto x3091 = host_outs.at(3);
        auto x3092 = host_outs.at(4);
        auto x3093 = host_outs.at(5);
        auto x3094 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3088);
          reg = x3088;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3089);
          reg = x3089;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3090);
          reg = x3090;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3091);
          reg = x3091;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3092);
          reg = x3092;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3093);
          reg = x3093;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3094);
          reg = x3094;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x3095 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x3095 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x3096 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x3096 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x3097 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x3097 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3098 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x3098 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3099 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x3099 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3100 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x3100 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3101 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x3101 != Fp::invalid());
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3102 = args[2][125 * steps + ((cycle - 0) & mask)];
      assert(x3102 != Fp::invalid());
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3103 = args[2][126 * steps + ((cycle - 0) & mask)];
      assert(x3103 != Fp::invalid());
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3104 = args[2][127 * steps + ((cycle - 0) & mask)];
      assert(x3104 != Fp::invalid());
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3105 = args[2][128 * steps + ((cycle - 0) & mask)];
      assert(x3105 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3106 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x3106 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3107 = x3095 - x3106;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3108 = (x3107 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x3109 = x7 - x3108;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][129 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3109);
          reg = x3109;
        }
      }
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3110 = args[2][129 * steps + ((cycle - 0) & mask)];
      assert(x3110 != Fp::invalid());
      if (x3110 != 0) {
        // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3111 = args[2][124 * steps + ((cycle - 0) & mask)];
        assert(x3111 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x3112 = x6 - x3111;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x3112 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3113 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x3113 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3114 = x3113 - x3095;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3115 = x3114 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3116 = Fp(x3115.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3116);
            reg = x3116;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3117 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x3117 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3118 = x3115 - x3117;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3119 = x3118 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3120 = Fp(x3119.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3120);
            reg = x3120;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3121 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x3121 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3122 = x3119 - x3121;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3123 = x3122 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3124 = Fp(x3123.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3124);
            reg = x3124;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3125 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x3125 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3126 = x3123 - x3125;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3127 = x3126 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3127);
          reg = x3127;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x3128 = x7 - x3110;
      if (x3128 != 0) {
        // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3129 = args[2][124 * steps + ((cycle - 0) & mask)];
        assert(x3129 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x3130 = x7 - x3129;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x3131 = x5 - x3129;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x3132 = x3130 * x3131;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x3132 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3133 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x3133 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x3134 = x3095 - x3133;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x3134 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3135 = args[2][123 * steps + ((cycle - 0) & mask)];
        assert(x3135 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3136 = x3135 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3137 = x3136 + x3129;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3138 = x3096 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3139 = x3137 - x3138;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3140 = x3139 + x3097;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3141 = Fp(x3140.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3141);
            reg = x3141;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3142 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x3142 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3143 = x3140 - x3142;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3144 = x3143 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3145 = Fp(x3144.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3145);
            reg = x3145;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3146 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x3146 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3147 = x3144 - x3146;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3148 = x3147 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3149 = Fp(x3148.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3149);
            reg = x3149;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3150 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x3150 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3151 = x3148 - x3150;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3152 = x3151 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3152);
          reg = x3152;
        }
        if (x3131 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3153 = x3098 - x3102;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3153 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3154 = x3099 - x3103;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3154 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3155 = x3100 - x3104;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3155 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3156 = x3101 - x3105;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3156 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("cirgen/components/ram.cpp":51:40))
      auto x3157 = args[2][122 * steps + ((cycle - 0) & mask)];
      assert(x3157 != Fp::invalid());
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x3158 = args[2][123 * steps + ((cycle - 0) & mask)];
      assert(x3158 != Fp::invalid());
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x3159 = args[2][124 * steps + ((cycle - 0) & mask)];
      assert(x3159 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3160 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x3160 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3161 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x3161 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3162 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x3162 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3163 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x3163 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3164 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x3164 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3165 = x3157 - x3164;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3166 = (x3165 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x3167 = x7 - x3166;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][130 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3167);
          reg = x3167;
        }
      }
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3168 = args[2][130 * steps + ((cycle - 0) & mask)];
      assert(x3168 != Fp::invalid());
      if (x3168 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3169 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x3169 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x3170 = x6 - x3169;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x3170 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3171 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x3171 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3172 = x3171 - x3157;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3173 = x3172 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3174 = Fp(x3173.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3174);
            reg = x3174;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3175 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x3175 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3176 = x3173 - x3175;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3177 = x3176 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3178 = Fp(x3177.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3178);
            reg = x3178;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3179 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x3179 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3180 = x3177 - x3179;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3181 = x3180 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3182 = Fp(x3181.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3182);
            reg = x3182;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3183 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x3183 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3184 = x3181 - x3183;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3185 = x3184 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3185);
          reg = x3185;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x3186 = x7 - x3168;
      if (x3186 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3187 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x3187 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x3188 = x7 - x3187;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x3189 = x5 - x3187;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x3190 = x3188 * x3189;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x3190 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3191 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x3191 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x3192 = x3157 - x3191;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x3192 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3193 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x3193 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3194 = x3193 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3195 = x3194 + x3187;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3196 = x3158 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3197 = x3195 - x3196;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3198 = x3197 + x3159;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3199 = Fp(x3198.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3199);
            reg = x3199;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3200 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x3200 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3201 = x3198 - x3200;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3202 = x3201 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3203 = Fp(x3202.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3203);
            reg = x3203;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3204 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x3204 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3205 = x3202 - x3204;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3206 = x3205 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3207 = Fp(x3206.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3207);
            reg = x3207;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3208 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x3208 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3209 = x3206 - x3208;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3210 = x3209 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3210);
          reg = x3210;
        }
        if (x3189 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3211 = x3102 - x3160;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3211 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3212 = x3103 - x3161;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3212 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3213 = x3104 - x3162;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3213 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3214 = x3105 - x3163;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3214 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x3215 = args[2][106 * steps + ((cycle - 0) & mask)];
    assert(x3215 != Fp::invalid());
    if (x3215 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x3216 = host_outs.at(0);
        auto x3217 = host_outs.at(1);
        auto x3218 = host_outs.at(2);
        auto x3219 = host_outs.at(3);
        auto x3220 = host_outs.at(4);
        auto x3221 = host_outs.at(5);
        auto x3222 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3216);
          reg = x3216;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3217);
          reg = x3217;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3218);
          reg = x3218;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3219);
          reg = x3219;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3220);
          reg = x3220;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][141 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3221);
          reg = x3221;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3222);
          reg = x3222;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x3223 = host_outs.at(0);
        auto x3224 = host_outs.at(1);
        auto x3225 = host_outs.at(2);
        auto x3226 = host_outs.at(3);
        auto x3227 = host_outs.at(4);
        auto x3228 = host_outs.at(5);
        auto x3229 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3223);
          reg = x3223;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3224);
          reg = x3224;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3225);
          reg = x3225;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3226);
          reg = x3226;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3227);
          reg = x3227;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3228);
          reg = x3228;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3229);
          reg = x3229;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x3230 = host_outs.at(0);
        auto x3231 = host_outs.at(1);
        auto x3232 = host_outs.at(2);
        auto x3233 = host_outs.at(3);
        auto x3234 = host_outs.at(4);
        auto x3235 = host_outs.at(5);
        auto x3236 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3230);
          reg = x3230;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3231);
          reg = x3231;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3232);
          reg = x3232;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3233);
          reg = x3233;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3234);
          reg = x3234;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3235);
          reg = x3235;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3236);
          reg = x3236;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x3237 = host_outs.at(0);
        auto x3238 = host_outs.at(1);
        auto x3239 = host_outs.at(2);
        auto x3240 = host_outs.at(3);
        auto x3241 = host_outs.at(4);
        auto x3242 = host_outs.at(5);
        auto x3243 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3237);
          reg = x3237;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3238);
          reg = x3238;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3239);
          reg = x3239;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3240);
          reg = x3240;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3241);
          reg = x3241;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3242);
          reg = x3242;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3243);
          reg = x3243;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x3244 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x3244 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x3245 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x3245 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x3246 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x3246 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3247 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x3247 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3248 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x3248 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3249 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x3249 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3250 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x3250 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3251 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x3251 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3252 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x3252 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3253 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x3253 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3254 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x3254 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3255 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x3255 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3256 = x3244 - x3255;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3257 = (x3256 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x3258 = x7 - x3257;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3258);
          reg = x3258;
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3259 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x3259 != Fp::invalid());
      if (x3259 != 0) {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3260 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x3260 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x3261 = x6 - x3260;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x3261 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3262 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x3262 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3263 = x3262 - x3244;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3264 = x3263 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3265 = Fp(x3264.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3265);
            reg = x3265;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3266 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x3266 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3267 = x3264 - x3266;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3268 = x3267 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3269 = Fp(x3268.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3269);
            reg = x3269;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3270 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x3270 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3271 = x3268 - x3270;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3272 = x3271 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3273 = Fp(x3272.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3273);
            reg = x3273;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3274 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x3274 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3275 = x3272 - x3274;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3276 = x3275 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3276);
          reg = x3276;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x3277 = x7 - x3259;
      if (x3277 != 0) {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3278 = args[2][138 * steps + ((cycle - 0) & mask)];
        assert(x3278 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x3279 = x7 - x3278;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x3280 = x5 - x3278;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x3281 = x3279 * x3280;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x3281 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3282 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x3282 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x3283 = x3244 - x3282;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x3283 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3284 = args[2][137 * steps + ((cycle - 0) & mask)];
        assert(x3284 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3285 = x3284 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3286 = x3285 + x3278;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3287 = x3245 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3288 = x3286 - x3287;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3289 = x3288 + x3246;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3290 = Fp(x3289.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3290);
            reg = x3290;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3291 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x3291 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3292 = x3289 - x3291;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3293 = x3292 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3294 = Fp(x3293.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3294);
            reg = x3294;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3295 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x3295 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3296 = x3293 - x3295;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3297 = x3296 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3298 = Fp(x3297.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3298);
            reg = x3298;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3299 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x3299 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3300 = x3297 - x3299;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3301 = x3300 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3301);
          reg = x3301;
        }
        if (x3280 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3302 = x3247 - x3251;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3302 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3303 = x3248 - x3252;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3303 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3304 = x3249 - x3253;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3304 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3305 = x3250 - x3254;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3305 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/Reg"("cirgen/components/ram.cpp":51:40))
      auto x3306 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x3306 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x3307 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x3307 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x3308 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x3308 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3309 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x3309 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3310 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x3310 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3311 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x3311 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3312 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x3312 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3313 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x3313 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3314 = x3306 - x3313;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3315 = (x3314 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x3316 = x7 - x3315;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3316);
          reg = x3316;
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3317 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x3317 != Fp::invalid());
      if (x3317 != 0) {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3318 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x3318 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x3319 = x6 - x3318;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x3319 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3320 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x3320 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3321 = x3320 - x3306;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3322 = x3321 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3323 = Fp(x3322.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3323);
            reg = x3323;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3324 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x3324 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3325 = x3322 - x3324;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3326 = x3325 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3327 = Fp(x3326.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3327);
            reg = x3327;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3328 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x3328 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3329 = x3326 - x3328;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3330 = x3329 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3331 = Fp(x3330.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3331);
            reg = x3331;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3332 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x3332 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3333 = x3330 - x3332;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3334 = x3333 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3334);
          reg = x3334;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x3335 = x7 - x3317;
      if (x3335 != 0) {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3336 = args[2][145 * steps + ((cycle - 0) & mask)];
        assert(x3336 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x3337 = x7 - x3336;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x3338 = x5 - x3336;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x3339 = x3337 * x3338;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x3339 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3340 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x3340 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x3341 = x3306 - x3340;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x3341 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3342 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x3342 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3343 = x3342 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3344 = x3343 + x3336;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3345 = x3307 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3346 = x3344 - x3345;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3347 = x3346 + x3308;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3348 = Fp(x3347.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3348);
            reg = x3348;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3349 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x3349 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3350 = x3347 - x3349;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3351 = x3350 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3352 = Fp(x3351.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3352);
            reg = x3352;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3353 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x3353 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3354 = x3351 - x3353;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3355 = x3354 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3356 = Fp(x3355.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3356);
            reg = x3356;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3357 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x3357 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3358 = x3355 - x3357;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3359 = x3358 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3359);
          reg = x3359;
        }
        if (x3338 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3360 = x3251 - x3309;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3360 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3361 = x3252 - x3310;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3361 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3362 = x3253 - x3311;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3362 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3363 = x3254 - x3312;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3363 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/Reg"("cirgen/components/ram.cpp":51:40))
      auto x3364 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x3364 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x3365 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x3365 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x3366 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x3366 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3367 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x3367 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3368 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x3368 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3369 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x3369 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3370 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x3370 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3371 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x3371 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3372 = x3364 - x3371;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3373 = (x3372 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x3374 = x7 - x3373;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3374);
          reg = x3374;
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3375 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x3375 != Fp::invalid());
      if (x3375 != 0) {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3376 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x3376 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x3377 = x6 - x3376;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x3377 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3378 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x3378 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3379 = x3378 - x3364;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3380 = x3379 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3381 = Fp(x3380.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3381);
            reg = x3381;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3382 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x3382 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3383 = x3380 - x3382;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3384 = x3383 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3385 = Fp(x3384.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3385);
            reg = x3385;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3386 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x3386 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3387 = x3384 - x3386;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3388 = x3387 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3389 = Fp(x3388.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3389);
            reg = x3389;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3390 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x3390 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3391 = x3388 - x3390;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3392 = x3391 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3392);
          reg = x3392;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x3393 = x7 - x3375;
      if (x3393 != 0) {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3394 = args[2][152 * steps + ((cycle - 0) & mask)];
        assert(x3394 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x3395 = x7 - x3394;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x3396 = x5 - x3394;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x3397 = x3395 * x3396;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x3397 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3398 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x3398 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x3399 = x3364 - x3398;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x3399 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3400 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x3400 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3401 = x3400 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3402 = x3401 + x3394;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3403 = x3365 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3404 = x3402 - x3403;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3405 = x3404 + x3366;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3406 = Fp(x3405.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3406);
            reg = x3406;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3407 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x3407 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3408 = x3405 - x3407;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3409 = x3408 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3410 = Fp(x3409.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3410);
            reg = x3410;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3411 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x3411 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3412 = x3409 - x3411;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3413 = x3412 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3414 = Fp(x3413.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3414);
            reg = x3414;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3415 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x3415 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3416 = x3413 - x3415;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3417 = x3416 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3417);
          reg = x3417;
        }
        if (x3396 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3418 = x3309 - x3367;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3418 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3419 = x3310 - x3368;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3419 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3420 = x3311 - x3369;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3420 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3421 = x3312 - x3370;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3421 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg"("cirgen/components/ram.cpp":51:40))
      auto x3422 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x3422 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x3423 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x3423 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x3424 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x3424 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3425 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x3425 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3426 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x3426 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3427 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x3427 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3428 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x3428 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3429 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x3429 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3430 = x3422 - x3429;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3431 = (x3430 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x3432 = x7 - x3431;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3432);
          reg = x3432;
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkVerifier3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3433 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x3433 != Fp::invalid());
      if (x3433 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3434 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x3434 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x3435 = x6 - x3434;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x3435 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3436 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x3436 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3437 = x3436 - x3422;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3438 = x3437 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3439 = Fp(x3438.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3439);
            reg = x3439;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3440 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x3440 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3441 = x3438 - x3440;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3442 = x3441 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3443 = Fp(x3442.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3443);
            reg = x3443;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3444 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x3444 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3445 = x3442 - x3444;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3446 = x3445 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3447 = Fp(x3446.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3447);
            reg = x3447;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3448 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x3448 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3449 = x3446 - x3448;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3450 = x3449 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3450);
          reg = x3450;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x3451 = x7 - x3433;
      if (x3451 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3452 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x3452 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x3453 = x7 - x3452;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x3454 = x5 - x3452;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x3455 = x3453 * x3454;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x3455 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3456 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x3456 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x3457 = x3422 - x3456;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x3457 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3458 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x3458 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3459 = x3458 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3460 = x3459 + x3452;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3461 = x3423 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3462 = x3460 - x3461;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3463 = x3462 + x3424;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3464 = Fp(x3463.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3464);
            reg = x3464;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3465 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x3465 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3466 = x3463 - x3465;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3467 = x3466 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3468 = Fp(x3467.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3468);
            reg = x3468;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3469 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x3469 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3470 = x3467 - x3469;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3471 = x3470 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3472 = Fp(x3471.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3472);
            reg = x3472;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3473 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x3473 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3474 = x3471 - x3473;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3475 = x3474 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3475);
          reg = x3475;
        }
        if (x3454 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3476 = x3367 - x3425;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3476 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3477 = x3368 - x3426;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3477 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3478 = x3369 - x3427;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3478 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3479 = x3370 - x3428;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3479 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x3480 = args[2][107 * steps + ((cycle - 0) & mask)];
    assert(x3480 != Fp::invalid());
    if (x3480 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x3481 = host_outs.at(0);
        auto x3482 = host_outs.at(1);
        auto x3483 = host_outs.at(2);
        auto x3484 = host_outs.at(3);
        auto x3485 = host_outs.at(4);
        auto x3486 = host_outs.at(5);
        auto x3487 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3481);
          reg = x3481;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3482);
          reg = x3482;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3483);
          reg = x3483;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3484);
          reg = x3484;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3485);
          reg = x3485;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3486);
          reg = x3486;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3487);
          reg = x3487;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x3488 = host_outs.at(0);
        auto x3489 = host_outs.at(1);
        auto x3490 = host_outs.at(2);
        auto x3491 = host_outs.at(3);
        auto x3492 = host_outs.at(4);
        auto x3493 = host_outs.at(5);
        auto x3494 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3488);
          reg = x3488;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3489);
          reg = x3489;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3490);
          reg = x3490;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3491);
          reg = x3491;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3492);
          reg = x3492;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3493);
          reg = x3493;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][161 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3494);
          reg = x3494;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x3495 = host_outs.at(0);
        auto x3496 = host_outs.at(1);
        auto x3497 = host_outs.at(2);
        auto x3498 = host_outs.at(3);
        auto x3499 = host_outs.at(4);
        auto x3500 = host_outs.at(5);
        auto x3501 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][162 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3495);
          reg = x3495;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][163 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3496);
          reg = x3496;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][164 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3497);
          reg = x3497;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][165 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3498);
          reg = x3498;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][166 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3499);
          reg = x3499;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][167 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3500);
          reg = x3500;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3501);
          reg = x3501;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x3502 = host_outs.at(0);
        auto x3503 = host_outs.at(1);
        auto x3504 = host_outs.at(2);
        auto x3505 = host_outs.at(3);
        auto x3506 = host_outs.at(4);
        auto x3507 = host_outs.at(5);
        auto x3508 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":36:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3502);
          reg = x3502;
        }
        // loc("cirgen/components/ram.cpp":37:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3503);
          reg = x3503;
        }
        // loc("cirgen/components/ram.cpp":38:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3504);
          reg = x3504;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3505);
          reg = x3505;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3506);
          reg = x3506;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3507);
          reg = x3507;
        }
        // loc("cirgen/components/u32.cpp":82:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3508);
          reg = x3508;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
      auto x3509 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x3509 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x3510 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x3510 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x3511 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x3511 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3512 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x3512 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3513 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x3513 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3514 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x3514 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3515 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x3515 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3516 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x3516 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3517 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x3517 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3518 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x3518 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3519 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x3519 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3520 = args[2][148 * steps + ((cycle - 0) & mask)];
        assert(x3520 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3521 = x3509 - x3520;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3522 = (x3521 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x3523 = x7 - x3522;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][169 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3523);
          reg = x3523;
        }
      }
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3524 = args[2][169 * steps + ((cycle - 0) & mask)];
      assert(x3524 != Fp::invalid());
      if (x3524 != 0) {
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3525 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x3525 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x3526 = x6 - x3525;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x3526 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3527 = args[2][148 * steps + ((cycle - 0) & mask)];
        assert(x3527 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3528 = x3527 - x3509;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3529 = x3528 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3530 = Fp(x3529.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3530);
            reg = x3530;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3531 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x3531 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3532 = x3529 - x3531;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3533 = x3532 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3534 = Fp(x3533.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3534);
            reg = x3534;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3535 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x3535 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3536 = x3533 - x3535;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3537 = x3536 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3538 = Fp(x3537.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3538);
            reg = x3538;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3539 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x3539 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3540 = x3537 - x3539;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3541 = x3540 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3541);
          reg = x3541;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x3542 = x7 - x3524;
      if (x3542 != 0) {
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3543 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x3543 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x3544 = x7 - x3543;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x3545 = x5 - x3543;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x3546 = x3544 * x3545;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x3546 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3547 = args[2][148 * steps + ((cycle - 0) & mask)];
        assert(x3547 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x3548 = x3509 - x3547;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x3548 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement4/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3549 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x3549 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3550 = x3549 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3551 = x3550 + x3543;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3552 = x3510 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3553 = x3551 - x3552;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3554 = x3553 + x3511;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3555 = Fp(x3554.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3555);
            reg = x3555;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3556 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x3556 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3557 = x3554 - x3556;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3558 = x3557 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3559 = Fp(x3558.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3559);
            reg = x3559;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3560 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x3560 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3561 = x3558 - x3560;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3562 = x3561 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3563 = Fp(x3562.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3563);
            reg = x3563;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3564 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x3564 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3565 = x3562 - x3564;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3566 = x3565 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3566);
          reg = x3566;
        }
        if (x3545 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3567 = x3512 - x3516;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3567 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3568 = x3513 - x3517;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3568 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3569 = x3514 - x3518;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3569 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3570 = x3515 - x3519;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3570 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement4/Reg"("cirgen/components/ram.cpp":51:40))
      auto x3571 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x3571 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement4/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x3572 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x3572 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement4/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x3573 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x3573 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3574 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x3574 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3575 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x3575 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3576 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x3576 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3577 = args[2][161 * steps + ((cycle - 0) & mask)];
      assert(x3577 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3578 = args[2][155 * steps + ((cycle - 0) & mask)];
        assert(x3578 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3579 = x3571 - x3578;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3580 = (x3579 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x3581 = x7 - x3580;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3581);
          reg = x3581;
        }
      }
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3582 = args[2][170 * steps + ((cycle - 0) & mask)];
      assert(x3582 != Fp::invalid());
      if (x3582 != 0) {
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3583 = args[2][157 * steps + ((cycle - 0) & mask)];
        assert(x3583 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x3584 = x6 - x3583;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x3584 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3585 = args[2][155 * steps + ((cycle - 0) & mask)];
        assert(x3585 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3586 = x3585 - x3571;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3587 = x3586 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3588 = Fp(x3587.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3588);
            reg = x3588;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3589 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x3589 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3590 = x3587 - x3589;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3591 = x3590 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3592 = Fp(x3591.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3592);
            reg = x3592;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3593 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x3593 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3594 = x3591 - x3593;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3595 = x3594 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3596 = Fp(x3595.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3596);
            reg = x3596;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3597 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x3597 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3598 = x3595 - x3597;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3599 = x3598 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3599);
          reg = x3599;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x3600 = x7 - x3582;
      if (x3600 != 0) {
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3601 = args[2][157 * steps + ((cycle - 0) & mask)];
        assert(x3601 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x3602 = x7 - x3601;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x3603 = x5 - x3601;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x3604 = x3602 * x3603;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x3604 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3605 = args[2][155 * steps + ((cycle - 0) & mask)];
        assert(x3605 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x3606 = x3571 - x3605;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x3606 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement5/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3607 = args[2][156 * steps + ((cycle - 0) & mask)];
        assert(x3607 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3608 = x3607 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3609 = x3608 + x3601;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3610 = x3572 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3611 = x3609 - x3610;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3612 = x3611 + x3573;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3613 = Fp(x3612.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3613);
            reg = x3613;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3614 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x3614 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3615 = x3612 - x3614;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3616 = x3615 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3617 = Fp(x3616.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3617);
            reg = x3617;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3618 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x3618 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3619 = x3616 - x3618;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3620 = x3619 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3621 = Fp(x3620.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3621);
            reg = x3621;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3622 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x3622 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3623 = x3620 - x3622;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3624 = x3623 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3624);
          reg = x3624;
        }
        if (x3603 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3625 = x3516 - x3574;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3625 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3626 = x3517 - x3575;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3626 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3627 = x3518 - x3576;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3627 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3628 = x3519 - x3577;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3628 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement5/Reg"("cirgen/components/ram.cpp":51:40))
      auto x3629 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x3629 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement5/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x3630 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x3630 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement5/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x3631 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x3631 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3632 = args[2][165 * steps + ((cycle - 0) & mask)];
      assert(x3632 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3633 = args[2][166 * steps + ((cycle - 0) & mask)];
      assert(x3633 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3634 = args[2][167 * steps + ((cycle - 0) & mask)];
      assert(x3634 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3635 = args[2][168 * steps + ((cycle - 0) & mask)];
      assert(x3635 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3636 = args[2][162 * steps + ((cycle - 0) & mask)];
        assert(x3636 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3637 = x3629 - x3636;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3638 = (x3637 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x3639 = x7 - x3638;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][171 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3639);
          reg = x3639;
        }
      }
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3640 = args[2][171 * steps + ((cycle - 0) & mask)];
      assert(x3640 != Fp::invalid());
      if (x3640 != 0) {
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3641 = args[2][164 * steps + ((cycle - 0) & mask)];
        assert(x3641 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x3642 = x6 - x3641;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x3642 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3643 = args[2][162 * steps + ((cycle - 0) & mask)];
        assert(x3643 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3644 = x3643 - x3629;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3645 = x3644 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3646 = Fp(x3645.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3646);
            reg = x3646;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3647 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x3647 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3648 = x3645 - x3647;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3649 = x3648 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3650 = Fp(x3649.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3650);
            reg = x3650;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3651 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x3651 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3652 = x3649 - x3651;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3653 = x3652 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3654 = Fp(x3653.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][25 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3654);
            reg = x3654;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3655 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x3655 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3656 = x3653 - x3655;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3657 = x3656 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][78 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3657);
          reg = x3657;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x3658 = x7 - x3640;
      if (x3658 != 0) {
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3659 = args[2][164 * steps + ((cycle - 0) & mask)];
        assert(x3659 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x3660 = x7 - x3659;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x3661 = x5 - x3659;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x3662 = x3660 * x3661;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x3662 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3663 = args[2][162 * steps + ((cycle - 0) & mask)];
        assert(x3663 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x3664 = x3629 - x3663;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x3664 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3665 = args[2][163 * steps + ((cycle - 0) & mask)];
        assert(x3665 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3666 = x3665 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3667 = x3666 + x3659;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3668 = x3630 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3669 = x3667 - x3668;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3670 = x3669 + x3631;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3671 = Fp(x3670.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3671);
            reg = x3671;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3672 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x3672 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3673 = x3670 - x3672;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3674 = x3673 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3675 = Fp(x3674.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3675);
            reg = x3675;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3676 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x3676 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3677 = x3674 - x3676;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3678 = x3677 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3679 = Fp(x3678.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][25 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3679);
            reg = x3679;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3680 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x3680 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3681 = x3678 - x3680;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3682 = x3681 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][78 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3682);
          reg = x3682;
        }
        if (x3661 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3683 = x3574 - x3632;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3683 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3684 = x3575 - x3633;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3684 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3685 = x3576 - x3634;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3685 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3686 = x3577 - x3635;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3686 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        }
      }
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement6/Reg"("cirgen/components/ram.cpp":51:40))
      auto x3687 = args[2][162 * steps + ((cycle - 0) & mask)];
      assert(x3687 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement6/Reg1"("cirgen/components/ram.cpp":52:42))
      auto x3688 = args[2][163 * steps + ((cycle - 0) & mask)];
      assert(x3688 != Fp::invalid());
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkElement6/Reg2"("cirgen/components/ram.cpp":53:42))
      auto x3689 = args[2][164 * steps + ((cycle - 0) & mask)];
      assert(x3689 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3690 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x3690 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3691 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x3691 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3692 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x3692 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3693 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x3693 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3694 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x3694 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3695 = x3687 - x3694;
        // loc("cirgen/components/ram.cpp":68:35)
        auto x3696 = (x3695 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":68:27)
        auto x3697 = x7 - x3696;
        // loc("cirgen/components/ram.cpp":68:12)
        {
          auto& reg = args[2][172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3697);
          reg = x3697;
        }
      }
      // loc("Top/Mux/4/Mux/13/RamBody/PlonkBody/RamPlonkVerifier3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3698 = args[2][172 * steps + ((cycle - 0) & mask)];
      assert(x3698 != Fp::invalid());
      if (x3698 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3699 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x3699 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":80:9)
        auto x3700 = x6 - x3699;
        // loc("cirgen/components/ram.cpp":80:9)
        if (x3700 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3701 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x3701 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3702 = x3701 - x3687;
        // loc("cirgen/components/ram.cpp":82:17)
        auto x3703 = x3702 - x7;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3704 = Fp(x3703.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][26 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3704);
            reg = x3704;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3705 = args[2][26 * steps + ((cycle - 0) & mask)];
        assert(x3705 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3706 = x3703 - x3705;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3707 = x3706 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3708 = Fp(x3707.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][27 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3708);
            reg = x3708;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3709 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x3709 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3710 = x3707 - x3709;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3711 = x3710 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3712 = Fp(x3711.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][28 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3712);
            reg = x3712;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement9/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3713 = args[2][28 * steps + ((cycle - 0) & mask)];
        assert(x3713 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3714 = x3711 - x3713;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3715 = x3714 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][79 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3715);
          reg = x3715;
        }
      }
      // loc("cirgen/components/ram.cpp":86:19)
      auto x3716 = x7 - x3698;
      if (x3716 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3717 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x3717 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":88:10)
        auto x3718 = x7 - x3717;
        // loc("cirgen/components/ram.cpp":88:45)
        auto x3719 = x5 - x3717;
        // loc("cirgen/components/ram.cpp":88:9)
        auto x3720 = x3718 * x3719;
        // loc("cirgen/components/ram.cpp":88:9)
        if (x3720 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3721 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x3721 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":90:9)
        auto x3722 = x3687 - x3721;
        // loc("cirgen/components/ram.cpp":90:9)
        if (x3722 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
        auto x3723 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x3723 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3724 = x3723 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3725 = x3724 + x3717;
        // loc("cirgen/components/ram.cpp":92:43)
        auto x3726 = x3688 * x2;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3727 = x3725 - x3726;
        // loc("cirgen/components/ram.cpp":92:17)
        auto x3728 = x3727 + x3689;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3729 = Fp(x3728.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][26 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3729);
            reg = x3729;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3730 = args[2][26 * steps + ((cycle - 0) & mask)];
        assert(x3730 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3731 = x3728 - x3730;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3732 = x3731 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3733 = Fp(x3732.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][27 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3733);
            reg = x3733;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("cirgen/components/bytes.cpp":83:16))
        auto x3734 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x3734 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3735 = x3732 - x3734;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3736 = x3735 * x3;
        {
          // loc("cirgen/components/bytes.cpp":82:21)
          auto x3737 = Fp(x3736.asUInt32() & x4.asUInt32());
          // loc("cirgen/components/bytes.cpp":82:12)
          {
            auto& reg = args[2][28 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3737);
            reg = x3737;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement9/Reg"("cirgen/components/bytes.cpp":83:16))
        auto x3738 = args[2][28 * steps + ((cycle - 0) & mask)];
        assert(x3738 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":83:11)
        auto x3739 = x3736 - x3738;
        // loc("cirgen/components/bytes.cpp":83:10)
        auto x3740 = x3739 * x3;
        // loc("./cirgen/components/bits.h":57:23)
        {
          auto& reg = args[2][79 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3740);
          reg = x3740;
        }
        if (x3719 != 0) {
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3741 = x3632 - x3690;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3741 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3742 = x3633 - x3691;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3742 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3743 = x3634 - x3692;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3743 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
          // loc("cirgen/components/ram.cpp":94:43)
          auto x3744 = x3635 - x3693;
          // loc("cirgen/components/ram.cpp":94:43)
          if (x3744 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
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
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":51:40))
    auto x3745 = args[2][2 * steps + ((cycle - 1) & mask)];
    assert(x3745 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":52:42))
    auto x3746 = args[2][3 * steps + ((cycle - 1) & mask)];
    assert(x3746 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":53:42))
    auto x3747 = args[2][4 * steps + ((cycle - 1) & mask)];
    assert(x3747 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3748 = args[2][5 * steps + ((cycle - 1) & mask)];
    assert(x3748 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3749 = args[2][6 * steps + ((cycle - 1) & mask)];
    assert(x3749 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3750 = args[2][7 * steps + ((cycle - 1) & mask)];
    assert(x3750 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3751 = args[2][8 * steps + ((cycle - 1) & mask)];
    assert(x3751 != Fp::invalid());
    // loc("Top/Mux/5/PlonkFini/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3752 = args[2][20 * steps + ((cycle - 0) & mask)];
    assert(x3752 != Fp::invalid());
    // loc("Top/Mux/5/PlonkFini/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3753 = args[2][21 * steps + ((cycle - 0) & mask)];
    assert(x3753 != Fp::invalid());
    // loc("Top/Mux/5/PlonkFini/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3754 = args[2][22 * steps + ((cycle - 0) & mask)];
    assert(x3754 != Fp::invalid());
    // loc("Top/Mux/5/PlonkFini/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3755 = args[2][23 * steps + ((cycle - 0) & mask)];
    assert(x3755 != Fp::invalid());
    {
      // loc("Top/Mux/5/PlonkFini/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x3756 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x3756 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:35)
      auto x3757 = x3745 - x3756;
      // loc("cirgen/components/ram.cpp":68:35)
      auto x3758 = (x3757 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":68:27)
      auto x3759 = x7 - x3758;
      // loc("cirgen/components/ram.cpp":68:12)
      {
        auto& reg = args[2][24 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3759);
        reg = x3759;
      }
    }
    // loc("Top/Mux/5/PlonkFini/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3760 = args[2][24 * steps + ((cycle - 0) & mask)];
    assert(x3760 != Fp::invalid());
    if (x3760 != 0) {
      // loc("Top/Mux/5/PlonkFini/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x3761 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x3761 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":80:9)
      auto x3762 = x6 - x3761;
      // loc("cirgen/components/ram.cpp":80:9)
      if (x3762 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:80");
      // loc("Top/Mux/5/PlonkFini/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x3763 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x3763 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":82:17)
      auto x3764 = x3763 - x3745;
      // loc("cirgen/components/ram.cpp":82:17)
      auto x3765 = x3764 - x7;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x3766 = Fp(x3765.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][10 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3766);
          reg = x3766;
        }
      }
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x3767 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x3767 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x3768 = x3765 - x3767;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x3769 = x3768 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x3770 = Fp(x3769.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][11 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3770);
          reg = x3770;
        }
      }
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x3771 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x3771 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x3772 = x3769 - x3771;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x3773 = x3772 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x3774 = Fp(x3773.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][12 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3774);
          reg = x3774;
        }
      }
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement1/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x3775 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x3775 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x3776 = x3773 - x3775;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x3777 = x3776 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][16 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3777);
        reg = x3777;
      }
    }
    // loc("cirgen/components/ram.cpp":86:19)
    auto x3778 = x7 - x3760;
    if (x3778 != 0) {
      // loc("Top/Mux/5/PlonkFini/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x3779 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x3779 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":88:10)
      auto x3780 = x7 - x3779;
      // loc("cirgen/components/ram.cpp":88:45)
      auto x3781 = x5 - x3779;
      // loc("cirgen/components/ram.cpp":88:9)
      auto x3782 = x3780 * x3781;
      // loc("cirgen/components/ram.cpp":88:9)
      if (x3782 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:88");
      // loc("Top/Mux/5/PlonkFini/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x3783 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x3783 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":90:9)
      auto x3784 = x3745 - x3783;
      // loc("cirgen/components/ram.cpp":90:9)
      if (x3784 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:90");
      // loc("Top/Mux/5/PlonkFini/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":113:61))
      auto x3785 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x3785 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":92:17)
      auto x3786 = x3785 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x3787 = x3786 + x3779;
      // loc("cirgen/components/ram.cpp":92:43)
      auto x3788 = x3746 * x2;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x3789 = x3787 - x3788;
      // loc("cirgen/components/ram.cpp":92:17)
      auto x3790 = x3789 + x3747;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x3791 = Fp(x3790.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][10 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3791);
          reg = x3791;
        }
      }
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x3792 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x3792 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x3793 = x3790 - x3792;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x3794 = x3793 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x3795 = Fp(x3794.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][11 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3795);
          reg = x3795;
        }
      }
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg1"("cirgen/components/bytes.cpp":83:16))
      auto x3796 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x3796 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x3797 = x3794 - x3796;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x3798 = x3797 * x3;
      {
        // loc("cirgen/components/bytes.cpp":82:21)
        auto x3799 = Fp(x3798.asUInt32() & x4.asUInt32());
        // loc("cirgen/components/bytes.cpp":82:12)
        {
          auto& reg = args[2][12 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3799);
          reg = x3799;
        }
      }
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement1/Reg"("cirgen/components/bytes.cpp":83:16))
      auto x3800 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x3800 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":83:11)
      auto x3801 = x3798 - x3800;
      // loc("cirgen/components/bytes.cpp":83:10)
      auto x3802 = x3801 * x3;
      // loc("./cirgen/components/bits.h":57:23)
      {
        auto& reg = args[2][16 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3802);
        reg = x3802;
      }
      if (x3781 != 0) {
        // loc("cirgen/components/ram.cpp":94:43)
        auto x3803 = x3748 - x3752;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x3803 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x3804 = x3749 - x3753;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x3804 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x3805 = x3750 - x3754;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x3805 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
        // loc("cirgen/components/ram.cpp":94:43)
        auto x3806 = x3751 - x3755;
        // loc("cirgen/components/ram.cpp":94:43)
        if (x3806 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:94");
      }
    }
  }
  if (x8 != 0) {
    {
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3807 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x3807 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3808 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x3808 != Fp::invalid());
      host_args.at(0) = x3807;
      host_args.at(1) = x3808;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement1/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3809 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x3809 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement1/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3810 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x3810 != Fp::invalid());
      host_args.at(0) = x3809;
      host_args.at(1) = x3810;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3811 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x3811 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement2/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3812 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x3812 != Fp::invalid());
      host_args.at(0) = x3811;
      host_args.at(1) = x3812;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3813 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x3813 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3814 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x3814 != Fp::invalid());
      host_args.at(0) = x3813;
      host_args.at(1) = x3814;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement4/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3815 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x3815 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement4/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3816 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x3816 != Fp::invalid());
      host_args.at(0) = x3815;
      host_args.at(1) = x3816;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement5/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3817 = args[2][20 * steps + ((cycle - 0) & mask)];
      assert(x3817 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement5/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3818 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x3818 != Fp::invalid());
      host_args.at(0) = x3817;
      host_args.at(1) = x3818;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement6/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3819 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x3819 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement6/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3820 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x3820 != Fp::invalid());
      host_args.at(0) = x3819;
      host_args.at(1) = x3820;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement7/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3821 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x3821 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement7/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3822 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x3822 != Fp::invalid());
      host_args.at(0) = x3821;
      host_args.at(1) = x3822;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement8/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3823 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x3823 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement8/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3824 = args[2][27 * steps + ((cycle - 0) & mask)];
      assert(x3824 != Fp::invalid());
      host_args.at(0) = x3823;
      host_args.at(1) = x3824;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement9/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3825 = args[2][28 * steps + ((cycle - 0) & mask)];
      assert(x3825 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement9/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3826 = args[2][29 * steps + ((cycle - 0) & mask)];
      assert(x3826 != Fp::invalid());
      host_args.at(0) = x3825;
      host_args.at(1) = x3826;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement10/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3827 = args[2][30 * steps + ((cycle - 0) & mask)];
      assert(x3827 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement10/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3828 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x3828 != Fp::invalid());
      host_args.at(0) = x3827;
      host_args.at(1) = x3828;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement11/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3829 = args[2][32 * steps + ((cycle - 0) & mask)];
      assert(x3829 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement11/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3830 = args[2][33 * steps + ((cycle - 0) & mask)];
      assert(x3830 != Fp::invalid());
      host_args.at(0) = x3829;
      host_args.at(1) = x3830;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement12/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3831 = args[2][34 * steps + ((cycle - 0) & mask)];
      assert(x3831 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement12/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3832 = args[2][35 * steps + ((cycle - 0) & mask)];
      assert(x3832 != Fp::invalid());
      host_args.at(0) = x3831;
      host_args.at(1) = x3832;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement13/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3833 = args[2][36 * steps + ((cycle - 0) & mask)];
      assert(x3833 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement13/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3834 = args[2][37 * steps + ((cycle - 0) & mask)];
      assert(x3834 != Fp::invalid());
      host_args.at(0) = x3833;
      host_args.at(1) = x3834;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement14/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3835 = args[2][38 * steps + ((cycle - 0) & mask)];
      assert(x3835 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement14/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3836 = args[2][39 * steps + ((cycle - 0) & mask)];
      assert(x3836 != Fp::invalid());
      host_args.at(0) = x3835;
      host_args.at(1) = x3836;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement15/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3837 = args[2][40 * steps + ((cycle - 0) & mask)];
      assert(x3837 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement15/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3838 = args[2][41 * steps + ((cycle - 0) & mask)];
      assert(x3838 != Fp::invalid());
      host_args.at(0) = x3837;
      host_args.at(1) = x3838;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement16/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3839 = args[2][42 * steps + ((cycle - 0) & mask)];
      assert(x3839 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement16/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3840 = args[2][43 * steps + ((cycle - 0) & mask)];
      assert(x3840 != Fp::invalid());
      host_args.at(0) = x3839;
      host_args.at(1) = x3840;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement17/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3841 = args[2][44 * steps + ((cycle - 0) & mask)];
      assert(x3841 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement17/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3842 = args[2][45 * steps + ((cycle - 0) & mask)];
      assert(x3842 != Fp::invalid());
      host_args.at(0) = x3841;
      host_args.at(1) = x3842;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement18/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3843 = args[2][46 * steps + ((cycle - 0) & mask)];
      assert(x3843 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement18/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3844 = args[2][47 * steps + ((cycle - 0) & mask)];
      assert(x3844 != Fp::invalid());
      host_args.at(0) = x3843;
      host_args.at(1) = x3844;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement19/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3845 = args[2][48 * steps + ((cycle - 0) & mask)];
      assert(x3845 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement19/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3846 = args[2][49 * steps + ((cycle - 0) & mask)];
      assert(x3846 != Fp::invalid());
      host_args.at(0) = x3845;
      host_args.at(1) = x3846;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement20/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3847 = args[2][50 * steps + ((cycle - 0) & mask)];
      assert(x3847 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement20/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3848 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x3848 != Fp::invalid());
      host_args.at(0) = x3847;
      host_args.at(1) = x3848;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
    }
  }
  if (x9 != 0) {
    {
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3849 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x3849 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3850 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x3850 != Fp::invalid());
      host_args.at(0) = x3849;
      host_args.at(1) = x3850;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement1/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3851 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x3851 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3852 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x3852 != Fp::invalid());
      host_args.at(0) = x3851;
      host_args.at(1) = x3852;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3853 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x3853 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3854 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x3854 != Fp::invalid());
      host_args.at(0) = x3853;
      host_args.at(1) = x3854;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3855 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x3855 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3856 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x3856 != Fp::invalid());
      host_args.at(0) = x3855;
      host_args.at(1) = x3856;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3857 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x3857 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3858 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x3858 != Fp::invalid());
      host_args.at(0) = x3857;
      host_args.at(1) = x3858;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3859 = args[2][20 * steps + ((cycle - 0) & mask)];
      assert(x3859 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3860 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x3860 != Fp::invalid());
      host_args.at(0) = x3859;
      host_args.at(1) = x3860;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3861 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x3861 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3862 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x3862 != Fp::invalid());
      host_args.at(0) = x3861;
      host_args.at(1) = x3862;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3863 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x3863 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3864 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x3864 != Fp::invalid());
      host_args.at(0) = x3863;
      host_args.at(1) = x3864;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3865 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x3865 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3866 = args[2][27 * steps + ((cycle - 0) & mask)];
      assert(x3866 != Fp::invalid());
      host_args.at(0) = x3865;
      host_args.at(1) = x3866;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement9/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3867 = args[2][28 * steps + ((cycle - 0) & mask)];
      assert(x3867 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement9/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3868 = args[2][29 * steps + ((cycle - 0) & mask)];
      assert(x3868 != Fp::invalid());
      host_args.at(0) = x3867;
      host_args.at(1) = x3868;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement10/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3869 = args[2][30 * steps + ((cycle - 0) & mask)];
      assert(x3869 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement10/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3870 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x3870 != Fp::invalid());
      host_args.at(0) = x3869;
      host_args.at(1) = x3870;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
    }
  }
  if (x10 != 0) {
    {
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3871 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x3871 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3872 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x3872 != Fp::invalid());
      host_args.at(0) = x3871;
      host_args.at(1) = x3872;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement1/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3873 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x3873 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3874 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x3874 != Fp::invalid());
      host_args.at(0) = x3873;
      host_args.at(1) = x3874;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3875 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x3875 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3876 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x3876 != Fp::invalid());
      host_args.at(0) = x3875;
      host_args.at(1) = x3876;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3877 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x3877 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3878 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x3878 != Fp::invalid());
      host_args.at(0) = x3877;
      host_args.at(1) = x3878;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3879 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x3879 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3880 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x3880 != Fp::invalid());
      host_args.at(0) = x3879;
      host_args.at(1) = x3880;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3881 = args[2][20 * steps + ((cycle - 0) & mask)];
      assert(x3881 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3882 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x3882 != Fp::invalid());
      host_args.at(0) = x3881;
      host_args.at(1) = x3882;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3883 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x3883 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3884 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x3884 != Fp::invalid());
      host_args.at(0) = x3883;
      host_args.at(1) = x3884;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3885 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x3885 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3886 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x3886 != Fp::invalid());
      host_args.at(0) = x3885;
      host_args.at(1) = x3886;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3887 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x3887 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3888 = args[2][27 * steps + ((cycle - 0) & mask)];
      assert(x3888 != Fp::invalid());
      host_args.at(0) = x3887;
      host_args.at(1) = x3888;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement9/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3889 = args[2][28 * steps + ((cycle - 0) & mask)];
      assert(x3889 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement9/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3890 = args[2][29 * steps + ((cycle - 0) & mask)];
      assert(x3890 != Fp::invalid());
      host_args.at(0) = x3889;
      host_args.at(1) = x3890;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement10/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3891 = args[2][30 * steps + ((cycle - 0) & mask)];
      assert(x3891 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement10/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3892 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x3892 != Fp::invalid());
      host_args.at(0) = x3891;
      host_args.at(1) = x3892;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement11/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3893 = args[2][32 * steps + ((cycle - 0) & mask)];
      assert(x3893 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement11/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3894 = args[2][33 * steps + ((cycle - 0) & mask)];
      assert(x3894 != Fp::invalid());
      host_args.at(0) = x3893;
      host_args.at(1) = x3894;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement12/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3895 = args[2][34 * steps + ((cycle - 0) & mask)];
      assert(x3895 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement12/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3896 = args[2][35 * steps + ((cycle - 0) & mask)];
      assert(x3896 != Fp::invalid());
      host_args.at(0) = x3895;
      host_args.at(1) = x3896;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement13/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3897 = args[2][36 * steps + ((cycle - 0) & mask)];
      assert(x3897 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement13/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3898 = args[2][37 * steps + ((cycle - 0) & mask)];
      assert(x3898 != Fp::invalid());
      host_args.at(0) = x3897;
      host_args.at(1) = x3898;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement14/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3899 = args[2][38 * steps + ((cycle - 0) & mask)];
      assert(x3899 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement14/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3900 = args[2][39 * steps + ((cycle - 0) & mask)];
      assert(x3900 != Fp::invalid());
      host_args.at(0) = x3899;
      host_args.at(1) = x3900;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement15/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3901 = args[2][40 * steps + ((cycle - 0) & mask)];
      assert(x3901 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement15/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3902 = args[2][41 * steps + ((cycle - 0) & mask)];
      assert(x3902 != Fp::invalid());
      host_args.at(0) = x3901;
      host_args.at(1) = x3902;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
    }
  }
  if (x11 != 0) {
    {
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3903 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x3903 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3904 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x3904 != Fp::invalid());
      host_args.at(0) = x3903;
      host_args.at(1) = x3904;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3905 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x3905 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3906 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x3906 != Fp::invalid());
      host_args.at(0) = x3905;
      host_args.at(1) = x3906;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3907 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x3907 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3908 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x3908 != Fp::invalid());
      host_args.at(0) = x3907;
      host_args.at(1) = x3908;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3909 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x3909 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3910 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x3910 != Fp::invalid());
      host_args.at(0) = x3909;
      host_args.at(1) = x3910;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3911 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x3911 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3912 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x3912 != Fp::invalid());
      host_args.at(0) = x3911;
      host_args.at(1) = x3912;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3913 = args[2][20 * steps + ((cycle - 0) & mask)];
      assert(x3913 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3914 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x3914 != Fp::invalid());
      host_args.at(0) = x3913;
      host_args.at(1) = x3914;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3915 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x3915 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3916 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x3916 != Fp::invalid());
      host_args.at(0) = x3915;
      host_args.at(1) = x3916;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3917 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x3917 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3918 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x3918 != Fp::invalid());
      host_args.at(0) = x3917;
      host_args.at(1) = x3918;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3919 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x3919 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3920 = args[2][27 * steps + ((cycle - 0) & mask)];
      assert(x3920 != Fp::invalid());
      host_args.at(0) = x3919;
      host_args.at(1) = x3920;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement9/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3921 = args[2][28 * steps + ((cycle - 0) & mask)];
      assert(x3921 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement9/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3922 = args[2][29 * steps + ((cycle - 0) & mask)];
      assert(x3922 != Fp::invalid());
      host_args.at(0) = x3921;
      host_args.at(1) = x3922;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement10/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3923 = args[2][30 * steps + ((cycle - 0) & mask)];
      assert(x3923 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement10/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3924 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x3924 != Fp::invalid());
      host_args.at(0) = x3923;
      host_args.at(1) = x3924;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement11/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3925 = args[2][32 * steps + ((cycle - 0) & mask)];
      assert(x3925 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement11/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3926 = args[2][33 * steps + ((cycle - 0) & mask)];
      assert(x3926 != Fp::invalid());
      host_args.at(0) = x3925;
      host_args.at(1) = x3926;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement12/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3927 = args[2][34 * steps + ((cycle - 0) & mask)];
      assert(x3927 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement12/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3928 = args[2][35 * steps + ((cycle - 0) & mask)];
      assert(x3928 != Fp::invalid());
      host_args.at(0) = x3927;
      host_args.at(1) = x3928;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement13/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3929 = args[2][36 * steps + ((cycle - 0) & mask)];
      assert(x3929 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement13/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3930 = args[2][37 * steps + ((cycle - 0) & mask)];
      assert(x3930 != Fp::invalid());
      host_args.at(0) = x3929;
      host_args.at(1) = x3930;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement14/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3931 = args[2][38 * steps + ((cycle - 0) & mask)];
      assert(x3931 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement14/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3932 = args[2][39 * steps + ((cycle - 0) & mask)];
      assert(x3932 != Fp::invalid());
      host_args.at(0) = x3931;
      host_args.at(1) = x3932;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement15/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3933 = args[2][40 * steps + ((cycle - 0) & mask)];
      assert(x3933 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement15/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3934 = args[2][41 * steps + ((cycle - 0) & mask)];
      assert(x3934 != Fp::invalid());
      host_args.at(0) = x3933;
      host_args.at(1) = x3934;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
    }
  }
  if (x12 != 0) {
    {
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3935 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x3935 != Fp::invalid());
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3936 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x3936 != Fp::invalid());
      host_args.at(0) = x3935;
      host_args.at(1) = x3936;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement1/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3937 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x3937 != Fp::invalid());
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x3938 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x3938 != Fp::invalid());
      host_args.at(0) = x3937;
      host_args.at(1) = x3938;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
    }
  }
  return x6;
}

} // namespace risc0::circuit::rv32im
// clang-format on
