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

Fp step_verify_bytes(void* ctx, HostBridge host, size_t steps, size_t cycle, Fp** args) {
  size_t mask = steps - 1;
  std::array<Fp, 32> host_args;
  std::array<Fp, 32> host_outs;
  // loc("cirgen/components/bytes.cpp":89:26)
  Fp x0(255);
  // loc("cirgen/components/bytes.cpp":37:25)
  Fp x1(2);
  // loc("cirgen/components/bytes.cpp":34:29)
  Fp x2(254);
  // loc("cirgen/components/bytes.cpp":21:13)
  Fp x3(0);
  // loc("cirgen/circuit/rv32im/top.cpp":18:17)
  Fp x4(1);
  // loc("Top/Code/OneHot/hot[1](Reg)"("./cirgen/components/mux.h":39:25))
  auto x5 = args[0][2 * steps + ((cycle - 0) & mask)];
  assert(x5 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[2](Reg)"("./cirgen/components/mux.h":39:25))
  auto x6 = args[0][3 * steps + ((cycle - 0) & mask)];
  assert(x6 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[3](Reg)"("./cirgen/components/mux.h":39:25))
  auto x7 = args[0][4 * steps + ((cycle - 0) & mask)];
  assert(x7 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[4](Reg)"("./cirgen/components/mux.h":39:25))
  auto x8 = args[0][5 * steps + ((cycle - 0) & mask)];
  assert(x8 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[5](Reg)"("./cirgen/components/mux.h":39:25))
  auto x9 = args[0][6 * steps + ((cycle - 0) & mask)];
  assert(x9 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[6](Reg)"("./cirgen/components/mux.h":39:25))
  auto x10 = args[0][7 * steps + ((cycle - 0) & mask)];
  assert(x10 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[0](Reg)"("cirgen/circuit/rv32im/top.cpp":71:27))
  auto x11 = args[0][1 * steps + ((cycle - 0) & mask)];
  assert(x11 != Fp::invalid());
  if (x11 != 0) {
    // loc("cirgen/components/bytes.cpp":21:3)
    {
      auto& reg = args[2][0 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x3);
      reg = x3;
    }
    // loc("cirgen/components/bytes.cpp":22:3)
    {
      auto& reg = args[2][1 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x3);
      reg = x3;
    }
  }
  if (x5 != 0) {
    {
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x12 = host_outs.at(0);
      auto x13 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x12);
        reg = x12;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x13);
        reg = x13;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x14 = host_outs.at(0);
      auto x15 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x14);
        reg = x14;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x15);
        reg = x15;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x16 = host_outs.at(0);
      auto x17 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x16);
        reg = x16;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x17);
        reg = x17;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x18 = host_outs.at(0);
      auto x19 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x18);
        reg = x18;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x19);
        reg = x19;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x20 = host_outs.at(0);
      auto x21 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x20);
        reg = x20;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x21);
        reg = x21;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x22 = host_outs.at(0);
      auto x23 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x22);
        reg = x22;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x23);
        reg = x23;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x24 = host_outs.at(0);
      auto x25 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x24);
        reg = x24;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x25);
        reg = x25;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x26 = host_outs.at(0);
      auto x27 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x26);
        reg = x26;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x27);
        reg = x27;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x28 = host_outs.at(0);
      auto x29 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x28);
        reg = x28;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x29);
        reg = x29;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x30 = host_outs.at(0);
      auto x31 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x30);
        reg = x30;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x31);
        reg = x31;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x32 = host_outs.at(0);
      auto x33 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x32);
        reg = x32;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][73 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x33);
        reg = x33;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x34 = host_outs.at(0);
      auto x35 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x34);
        reg = x34;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x35);
        reg = x35;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x36 = host_outs.at(0);
      auto x37 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x36);
        reg = x36;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x37);
        reg = x37;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x38 = host_outs.at(0);
      auto x39 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][78 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x38);
        reg = x38;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][79 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x39);
        reg = x39;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x40 = host_outs.at(0);
      auto x41 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][80 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x40);
        reg = x40;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][81 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x41);
        reg = x41;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x42 = host_outs.at(0);
      auto x43 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][82 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x42);
        reg = x42;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][83 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x43);
        reg = x43;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x44 = host_outs.at(0);
      auto x45 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][84 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x44);
        reg = x44;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][85 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x45);
        reg = x45;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x46 = host_outs.at(0);
      auto x47 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][86 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x46);
        reg = x46;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][87 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x47);
        reg = x47;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x48 = host_outs.at(0);
      auto x49 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][88 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x48);
        reg = x48;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x49);
        reg = x49;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x50 = host_outs.at(0);
      auto x51 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][90 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x50);
        reg = x50;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][91 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x51);
        reg = x51;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x52 = host_outs.at(0);
      auto x53 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x52);
        reg = x52;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x53);
        reg = x53;
      }
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":59:42))
    auto x54 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x54 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":60:40))
    auto x55 = args[2][1 * steps + ((cycle - 1) & mask)];
    assert(x55 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x56 = args[2][52 * steps + ((cycle - 0) & mask)];
    assert(x56 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x57 = args[2][53 * steps + ((cycle - 0) & mask)];
    assert(x57 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x58 = x56 - x54;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x59 = x57 - x55;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x60 = x58 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x61 = x58 * x60;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x61 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x58 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x57 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x62 = x55 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x63 = x55 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x64 = x62 * x63;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x64 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x65 = x4 - x58;
    if (x65 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x66 = x59 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x67 = x59 * x66;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x68 = x59 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x69 = x67 * x68;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x69 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x70 = args[2][54 * steps + ((cycle - 0) & mask)];
    assert(x70 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x71 = args[2][55 * steps + ((cycle - 0) & mask)];
    assert(x71 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x72 = x70 - x56;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x73 = x71 - x57;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x74 = x72 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x75 = x72 * x74;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x75 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x72 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x71 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x76 = x57 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x77 = x57 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x78 = x76 * x77;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x78 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x79 = x4 - x72;
    if (x79 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x80 = x73 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x81 = x73 * x80;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x82 = x73 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x83 = x81 * x82;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x83 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x84 = args[2][56 * steps + ((cycle - 0) & mask)];
    assert(x84 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x85 = args[2][57 * steps + ((cycle - 0) & mask)];
    assert(x85 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x86 = x84 - x70;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x87 = x85 - x71;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x88 = x86 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x89 = x86 * x88;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x89 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x86 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x85 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x90 = x71 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x91 = x71 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x92 = x90 * x91;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x92 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x93 = x4 - x86;
    if (x93 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x94 = x87 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x95 = x87 * x94;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x96 = x87 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x97 = x95 * x96;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x97 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x98 = args[2][58 * steps + ((cycle - 0) & mask)];
    assert(x98 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x99 = args[2][59 * steps + ((cycle - 0) & mask)];
    assert(x99 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x100 = x98 - x84;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x101 = x99 - x85;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x102 = x100 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x103 = x100 * x102;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x103 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x100 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x99 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x104 = x85 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x105 = x85 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x106 = x104 * x105;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x106 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x107 = x4 - x100;
    if (x107 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x108 = x101 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x109 = x101 * x108;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x110 = x101 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x111 = x109 * x110;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x111 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x112 = args[2][60 * steps + ((cycle - 0) & mask)];
    assert(x112 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x113 = args[2][61 * steps + ((cycle - 0) & mask)];
    assert(x113 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x114 = x112 - x98;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x115 = x113 - x99;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x116 = x114 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x117 = x114 * x116;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x117 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x114 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x113 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x118 = x99 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x119 = x99 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x120 = x118 * x119;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x120 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x121 = x4 - x114;
    if (x121 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x122 = x115 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x123 = x115 * x122;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x124 = x115 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x125 = x123 * x124;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x125 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x126 = args[2][62 * steps + ((cycle - 0) & mask)];
    assert(x126 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x127 = args[2][63 * steps + ((cycle - 0) & mask)];
    assert(x127 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x128 = x126 - x112;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x129 = x127 - x113;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x130 = x128 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x131 = x128 * x130;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x131 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x128 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x127 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x132 = x113 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x133 = x113 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x134 = x132 * x133;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x134 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x135 = x4 - x128;
    if (x135 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x136 = x129 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x137 = x129 * x136;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x138 = x129 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x139 = x137 * x138;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x139 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x140 = args[2][64 * steps + ((cycle - 0) & mask)];
    assert(x140 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x141 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x141 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x142 = x140 - x126;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x143 = x141 - x127;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x144 = x142 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x145 = x142 * x144;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x145 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x142 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x141 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x146 = x127 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x147 = x127 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x148 = x146 * x147;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x148 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x149 = x4 - x142;
    if (x149 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x150 = x143 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x151 = x143 * x150;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x152 = x143 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x153 = x151 * x152;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x153 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x154 = args[2][66 * steps + ((cycle - 0) & mask)];
    assert(x154 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x155 = args[2][67 * steps + ((cycle - 0) & mask)];
    assert(x155 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x156 = x154 - x140;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x157 = x155 - x141;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x158 = x156 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x159 = x156 * x158;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x159 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x156 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x155 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x160 = x141 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x161 = x141 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x162 = x160 * x161;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x162 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x163 = x4 - x156;
    if (x163 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x164 = x157 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x165 = x157 * x164;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x166 = x157 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x167 = x165 * x166;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x167 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x168 = args[2][68 * steps + ((cycle - 0) & mask)];
    assert(x168 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x169 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x169 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x170 = x168 - x154;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x171 = x169 - x155;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x172 = x170 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x173 = x170 * x172;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x173 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x170 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x169 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x174 = x155 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x175 = x155 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x176 = x174 * x175;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x176 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x177 = x4 - x170;
    if (x177 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x178 = x171 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x179 = x171 * x178;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x180 = x171 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x181 = x179 * x180;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x181 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x182 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x182 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x183 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x183 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x184 = x182 - x168;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x185 = x183 - x169;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x186 = x184 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x187 = x184 * x186;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x187 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x184 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x183 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x188 = x169 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x189 = x169 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x190 = x188 * x189;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x190 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x191 = x4 - x184;
    if (x191 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x192 = x185 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x193 = x185 * x192;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x194 = x185 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x195 = x193 * x194;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x195 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x196 = args[2][72 * steps + ((cycle - 0) & mask)];
    assert(x196 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x197 = args[2][73 * steps + ((cycle - 0) & mask)];
    assert(x197 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x198 = x196 - x182;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x199 = x197 - x183;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x200 = x198 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x201 = x198 * x200;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x201 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x198 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x197 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x202 = x183 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x203 = x183 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x204 = x202 * x203;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x204 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x205 = x4 - x198;
    if (x205 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x206 = x199 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x207 = x199 * x206;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x208 = x199 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x209 = x207 * x208;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x209 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x210 = args[2][74 * steps + ((cycle - 0) & mask)];
    assert(x210 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x211 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x211 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x212 = x210 - x196;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x213 = x211 - x197;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x214 = x212 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x215 = x212 * x214;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x215 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x212 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x211 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x216 = x197 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x217 = x197 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x218 = x216 * x217;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x218 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x219 = x4 - x212;
    if (x219 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x220 = x213 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x221 = x213 * x220;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x222 = x213 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x223 = x221 * x222;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x223 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x224 = args[2][76 * steps + ((cycle - 0) & mask)];
    assert(x224 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x225 = args[2][77 * steps + ((cycle - 0) & mask)];
    assert(x225 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x226 = x224 - x210;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x227 = x225 - x211;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x228 = x226 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x229 = x226 * x228;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x229 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x226 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x225 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x230 = x211 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x231 = x211 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x232 = x230 * x231;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x232 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x233 = x4 - x226;
    if (x233 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x234 = x227 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x235 = x227 * x234;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x236 = x227 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x237 = x235 * x236;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x237 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x238 = args[2][78 * steps + ((cycle - 0) & mask)];
    assert(x238 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x239 = args[2][79 * steps + ((cycle - 0) & mask)];
    assert(x239 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x240 = x238 - x224;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x241 = x239 - x225;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x242 = x240 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x243 = x240 * x242;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x243 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x240 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x239 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x244 = x225 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x245 = x225 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x246 = x244 * x245;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x246 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x247 = x4 - x240;
    if (x247 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x248 = x241 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x249 = x241 * x248;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x250 = x241 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x251 = x249 * x250;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x251 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x252 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x252 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x253 = args[2][81 * steps + ((cycle - 0) & mask)];
    assert(x253 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x254 = x252 - x238;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x255 = x253 - x239;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x256 = x254 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x257 = x254 * x256;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x257 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x254 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x253 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x258 = x239 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x259 = x239 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x260 = x258 * x259;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x260 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x261 = x4 - x254;
    if (x261 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x262 = x255 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x263 = x255 * x262;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x264 = x255 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x265 = x263 * x264;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x265 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x266 = args[2][82 * steps + ((cycle - 0) & mask)];
    assert(x266 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x267 = args[2][83 * steps + ((cycle - 0) & mask)];
    assert(x267 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x268 = x266 - x252;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x269 = x267 - x253;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x270 = x268 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x271 = x268 * x270;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x271 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x268 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x267 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x272 = x253 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x273 = x253 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x274 = x272 * x273;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x274 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x275 = x4 - x268;
    if (x275 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x276 = x269 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x277 = x269 * x276;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x278 = x269 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x279 = x277 * x278;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x279 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x280 = args[2][84 * steps + ((cycle - 0) & mask)];
    assert(x280 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x281 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x281 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x282 = x280 - x266;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x283 = x281 - x267;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x284 = x282 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x285 = x282 * x284;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x285 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x282 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x281 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x286 = x267 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x287 = x267 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x288 = x286 * x287;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x288 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x289 = x4 - x282;
    if (x289 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x290 = x283 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x291 = x283 * x290;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x292 = x283 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x293 = x291 * x292;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x293 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x294 = args[2][86 * steps + ((cycle - 0) & mask)];
    assert(x294 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x295 = args[2][87 * steps + ((cycle - 0) & mask)];
    assert(x295 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x296 = x294 - x280;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x297 = x295 - x281;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x298 = x296 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x299 = x296 * x298;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x299 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x296 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x295 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x300 = x281 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x301 = x281 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x302 = x300 * x301;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x302 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x303 = x4 - x296;
    if (x303 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x304 = x297 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x305 = x297 * x304;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x306 = x297 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x307 = x305 * x306;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x307 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x308 = args[2][88 * steps + ((cycle - 0) & mask)];
    assert(x308 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x309 = args[2][89 * steps + ((cycle - 0) & mask)];
    assert(x309 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x310 = x308 - x294;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x311 = x309 - x295;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x312 = x310 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x313 = x310 * x312;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x313 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x310 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x309 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x314 = x295 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x315 = x295 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x316 = x314 * x315;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x316 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x317 = x4 - x310;
    if (x317 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x318 = x311 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x319 = x311 * x318;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x320 = x311 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x321 = x319 * x320;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x321 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x322 = args[2][90 * steps + ((cycle - 0) & mask)];
    assert(x322 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x323 = args[2][91 * steps + ((cycle - 0) & mask)];
    assert(x323 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x324 = x322 - x308;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x325 = x323 - x309;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x326 = x324 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x327 = x324 * x326;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x327 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x324 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x323 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x328 = x309 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x329 = x309 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x330 = x328 * x329;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x330 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x331 = x4 - x324;
    if (x331 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x332 = x325 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x333 = x325 * x332;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x334 = x325 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x335 = x333 * x334;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x335 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x336 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x336 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x337 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x337 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x338 = x336 - x322;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x339 = x337 - x323;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x340 = x338 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x341 = x338 * x340;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x341 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x338 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x337 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x342 = x323 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x343 = x323 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x344 = x342 * x343;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x344 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x345 = x4 - x338;
    if (x345 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x346 = x339 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x347 = x339 * x346;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x348 = x339 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x349 = x347 * x348;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x349 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
  }
  if (x6 != 0) {
    {
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x350 = host_outs.at(0);
      auto x351 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][42 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x350);
        reg = x350;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][43 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x351);
        reg = x351;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x352 = host_outs.at(0);
      auto x353 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][44 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x352);
        reg = x352;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][45 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x353);
        reg = x353;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x354 = host_outs.at(0);
      auto x355 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][46 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x354);
        reg = x354;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][47 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x355);
        reg = x355;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x356 = host_outs.at(0);
      auto x357 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][48 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x356);
        reg = x356;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][49 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x357);
        reg = x357;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x358 = host_outs.at(0);
      auto x359 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x358);
        reg = x358;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x359);
        reg = x359;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x360 = host_outs.at(0);
      auto x361 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x360);
        reg = x360;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x361);
        reg = x361;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x362 = host_outs.at(0);
      auto x363 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x362);
        reg = x362;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x363);
        reg = x363;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x364 = host_outs.at(0);
      auto x365 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x364);
        reg = x364;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x365);
        reg = x365;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x366 = host_outs.at(0);
      auto x367 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x366);
        reg = x366;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x367);
        reg = x367;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x368 = host_outs.at(0);
      auto x369 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x368);
        reg = x368;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x369);
        reg = x369;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x370 = host_outs.at(0);
      auto x371 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x370);
        reg = x370;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x371);
        reg = x371;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x372 = host_outs.at(0);
      auto x373 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x372);
        reg = x372;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x373);
        reg = x373;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x374 = host_outs.at(0);
      auto x375 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x374);
        reg = x374;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x375);
        reg = x375;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x376 = host_outs.at(0);
      auto x377 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x376);
        reg = x376;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x377);
        reg = x377;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x378 = host_outs.at(0);
      auto x379 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x378);
        reg = x378;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x379);
        reg = x379;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x380 = host_outs.at(0);
      auto x381 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x380);
        reg = x380;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x381);
        reg = x381;
      }
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":59:42))
    auto x382 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x382 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":60:40))
    auto x383 = args[2][1 * steps + ((cycle - 1) & mask)];
    assert(x383 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x384 = args[2][42 * steps + ((cycle - 0) & mask)];
    assert(x384 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x385 = args[2][43 * steps + ((cycle - 0) & mask)];
    assert(x385 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x386 = x384 - x382;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x387 = x385 - x383;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x388 = x386 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x389 = x386 * x388;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x389 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x386 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x385 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x390 = x383 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x391 = x383 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x392 = x390 * x391;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x392 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x393 = x4 - x386;
    if (x393 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x394 = x387 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x395 = x387 * x394;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x396 = x387 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x397 = x395 * x396;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x397 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x398 = args[2][44 * steps + ((cycle - 0) & mask)];
    assert(x398 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x399 = args[2][45 * steps + ((cycle - 0) & mask)];
    assert(x399 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x400 = x398 - x384;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x401 = x399 - x385;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x402 = x400 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x403 = x400 * x402;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x403 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x400 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x399 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x404 = x385 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x405 = x385 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x406 = x404 * x405;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x406 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x407 = x4 - x400;
    if (x407 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x408 = x401 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x409 = x401 * x408;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x410 = x401 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x411 = x409 * x410;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x411 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x412 = args[2][46 * steps + ((cycle - 0) & mask)];
    assert(x412 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x413 = args[2][47 * steps + ((cycle - 0) & mask)];
    assert(x413 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x414 = x412 - x398;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x415 = x413 - x399;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x416 = x414 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x417 = x414 * x416;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x417 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x414 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x413 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x418 = x399 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x419 = x399 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x420 = x418 * x419;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x420 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x421 = x4 - x414;
    if (x421 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x422 = x415 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x423 = x415 * x422;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x424 = x415 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x425 = x423 * x424;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x425 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x426 = args[2][48 * steps + ((cycle - 0) & mask)];
    assert(x426 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x427 = args[2][49 * steps + ((cycle - 0) & mask)];
    assert(x427 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x428 = x426 - x412;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x429 = x427 - x413;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x430 = x428 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x431 = x428 * x430;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x431 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x428 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x427 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x432 = x413 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x433 = x413 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x434 = x432 * x433;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x434 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x435 = x4 - x428;
    if (x435 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x436 = x429 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x437 = x429 * x436;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x438 = x429 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x439 = x437 * x438;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x439 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x440 = args[2][50 * steps + ((cycle - 0) & mask)];
    assert(x440 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x441 = args[2][51 * steps + ((cycle - 0) & mask)];
    assert(x441 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x442 = x440 - x426;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x443 = x441 - x427;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x444 = x442 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x445 = x442 * x444;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x445 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x442 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x441 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x446 = x427 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x447 = x427 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x448 = x446 * x447;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x448 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x449 = x4 - x442;
    if (x449 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x450 = x443 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x451 = x443 * x450;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x452 = x443 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x453 = x451 * x452;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x453 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x454 = args[2][52 * steps + ((cycle - 0) & mask)];
    assert(x454 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x455 = args[2][53 * steps + ((cycle - 0) & mask)];
    assert(x455 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x456 = x454 - x440;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x457 = x455 - x441;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x458 = x456 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x459 = x456 * x458;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x459 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x456 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x455 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x460 = x441 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x461 = x441 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x462 = x460 * x461;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x462 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x463 = x4 - x456;
    if (x463 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x464 = x457 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x465 = x457 * x464;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x466 = x457 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x467 = x465 * x466;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x467 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x468 = args[2][54 * steps + ((cycle - 0) & mask)];
    assert(x468 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x469 = args[2][55 * steps + ((cycle - 0) & mask)];
    assert(x469 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x470 = x468 - x454;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x471 = x469 - x455;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x472 = x470 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x473 = x470 * x472;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x473 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x470 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x469 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x474 = x455 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x475 = x455 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x476 = x474 * x475;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x476 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x477 = x4 - x470;
    if (x477 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x478 = x471 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x479 = x471 * x478;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x480 = x471 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x481 = x479 * x480;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x481 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x482 = args[2][56 * steps + ((cycle - 0) & mask)];
    assert(x482 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x483 = args[2][57 * steps + ((cycle - 0) & mask)];
    assert(x483 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x484 = x482 - x468;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x485 = x483 - x469;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x486 = x484 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x487 = x484 * x486;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x487 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x484 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x483 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x488 = x469 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x489 = x469 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x490 = x488 * x489;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x490 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x491 = x4 - x484;
    if (x491 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x492 = x485 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x493 = x485 * x492;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x494 = x485 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x495 = x493 * x494;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x495 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x496 = args[2][58 * steps + ((cycle - 0) & mask)];
    assert(x496 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x497 = args[2][59 * steps + ((cycle - 0) & mask)];
    assert(x497 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x498 = x496 - x482;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x499 = x497 - x483;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x500 = x498 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x501 = x498 * x500;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x501 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x498 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x497 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x502 = x483 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x503 = x483 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x504 = x502 * x503;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x504 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x505 = x4 - x498;
    if (x505 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x506 = x499 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x507 = x499 * x506;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x508 = x499 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x509 = x507 * x508;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x509 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x510 = args[2][60 * steps + ((cycle - 0) & mask)];
    assert(x510 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x511 = args[2][61 * steps + ((cycle - 0) & mask)];
    assert(x511 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x512 = x510 - x496;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x513 = x511 - x497;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x514 = x512 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x515 = x512 * x514;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x515 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x512 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x511 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x516 = x497 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x517 = x497 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x518 = x516 * x517;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x518 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x519 = x4 - x512;
    if (x519 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x520 = x513 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x521 = x513 * x520;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x522 = x513 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x523 = x521 * x522;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x523 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x524 = args[2][62 * steps + ((cycle - 0) & mask)];
    assert(x524 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x525 = args[2][63 * steps + ((cycle - 0) & mask)];
    assert(x525 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x526 = x524 - x510;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x527 = x525 - x511;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x528 = x526 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x529 = x526 * x528;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x529 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x526 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x525 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x530 = x511 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x531 = x511 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x532 = x530 * x531;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x532 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x533 = x4 - x526;
    if (x533 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x534 = x527 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x535 = x527 * x534;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x536 = x527 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x537 = x535 * x536;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x537 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x538 = args[2][64 * steps + ((cycle - 0) & mask)];
    assert(x538 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x539 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x539 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x540 = x538 - x524;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x541 = x539 - x525;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x542 = x540 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x543 = x540 * x542;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x543 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x540 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x539 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x544 = x525 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x545 = x525 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x546 = x544 * x545;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x546 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x547 = x4 - x540;
    if (x547 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x548 = x541 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x549 = x541 * x548;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x550 = x541 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x551 = x549 * x550;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x551 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x552 = args[2][66 * steps + ((cycle - 0) & mask)];
    assert(x552 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x553 = args[2][67 * steps + ((cycle - 0) & mask)];
    assert(x553 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x554 = x552 - x538;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x555 = x553 - x539;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x556 = x554 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x557 = x554 * x556;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x557 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x554 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x553 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x558 = x539 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x559 = x539 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x560 = x558 * x559;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x560 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x561 = x4 - x554;
    if (x561 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x562 = x555 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x563 = x555 * x562;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x564 = x555 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x565 = x563 * x564;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x565 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x566 = args[2][68 * steps + ((cycle - 0) & mask)];
    assert(x566 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x567 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x567 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x568 = x566 - x552;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x569 = x567 - x553;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x570 = x568 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x571 = x568 * x570;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x571 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x568 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x567 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x572 = x553 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x573 = x553 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x574 = x572 * x573;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x574 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x575 = x4 - x568;
    if (x575 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x576 = x569 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x577 = x569 * x576;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x578 = x569 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x579 = x577 * x578;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x579 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x580 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x580 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x581 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x581 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x582 = x580 - x566;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x583 = x581 - x567;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x584 = x582 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x585 = x582 * x584;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x585 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x582 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x581 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x586 = x567 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x587 = x567 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x588 = x586 * x587;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x588 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x589 = x4 - x582;
    if (x589 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x590 = x583 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x591 = x583 * x590;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x592 = x583 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x593 = x591 * x592;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x593 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x594 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x594 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x595 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x595 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x596 = x594 - x580;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x597 = x595 - x581;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x598 = x596 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x599 = x596 * x598;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x599 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x596 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x595 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x600 = x581 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x601 = x581 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x602 = x600 * x601;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x602 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x603 = x4 - x596;
    if (x603 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x604 = x597 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x605 = x597 * x604;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x606 = x597 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x607 = x605 * x606;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x607 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
  }
  if (x7 != 0) {
    {
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x608 = host_outs.at(0);
      auto x609 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][42 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x608);
        reg = x608;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][43 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x609);
        reg = x609;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x610 = host_outs.at(0);
      auto x611 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][44 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x610);
        reg = x610;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][45 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x611);
        reg = x611;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x612 = host_outs.at(0);
      auto x613 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][46 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x612);
        reg = x612;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][47 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x613);
        reg = x613;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x614 = host_outs.at(0);
      auto x615 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][48 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x614);
        reg = x614;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][49 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x615);
        reg = x615;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x616 = host_outs.at(0);
      auto x617 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x616);
        reg = x616;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x617);
        reg = x617;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x618 = host_outs.at(0);
      auto x619 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x618);
        reg = x618;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x619);
        reg = x619;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x620 = host_outs.at(0);
      auto x621 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x620);
        reg = x620;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x621);
        reg = x621;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x622 = host_outs.at(0);
      auto x623 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x622);
        reg = x622;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x623);
        reg = x623;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x624 = host_outs.at(0);
      auto x625 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x624);
        reg = x624;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x625);
        reg = x625;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x626 = host_outs.at(0);
      auto x627 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x626);
        reg = x626;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x627);
        reg = x627;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x628 = host_outs.at(0);
      auto x629 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x628);
        reg = x628;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x629);
        reg = x629;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x630 = host_outs.at(0);
      auto x631 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x630);
        reg = x630;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x631);
        reg = x631;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x632 = host_outs.at(0);
      auto x633 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x632);
        reg = x632;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x633);
        reg = x633;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x634 = host_outs.at(0);
      auto x635 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x634);
        reg = x634;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x635);
        reg = x635;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x636 = host_outs.at(0);
      auto x637 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x636);
        reg = x636;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x637);
        reg = x637;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x638 = host_outs.at(0);
      auto x639 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x638);
        reg = x638;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x639);
        reg = x639;
      }
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":59:42))
    auto x640 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x640 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":60:40))
    auto x641 = args[2][1 * steps + ((cycle - 1) & mask)];
    assert(x641 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x642 = args[2][42 * steps + ((cycle - 0) & mask)];
    assert(x642 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x643 = args[2][43 * steps + ((cycle - 0) & mask)];
    assert(x643 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x644 = x642 - x640;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x645 = x643 - x641;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x646 = x644 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x647 = x644 * x646;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x647 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x644 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x643 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x648 = x641 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x649 = x641 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x650 = x648 * x649;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x650 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x651 = x4 - x644;
    if (x651 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x652 = x645 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x653 = x645 * x652;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x654 = x645 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x655 = x653 * x654;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x655 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x656 = args[2][44 * steps + ((cycle - 0) & mask)];
    assert(x656 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x657 = args[2][45 * steps + ((cycle - 0) & mask)];
    assert(x657 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x658 = x656 - x642;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x659 = x657 - x643;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x660 = x658 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x661 = x658 * x660;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x661 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x658 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x657 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x662 = x643 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x663 = x643 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x664 = x662 * x663;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x664 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x665 = x4 - x658;
    if (x665 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x666 = x659 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x667 = x659 * x666;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x668 = x659 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x669 = x667 * x668;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x669 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x670 = args[2][46 * steps + ((cycle - 0) & mask)];
    assert(x670 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x671 = args[2][47 * steps + ((cycle - 0) & mask)];
    assert(x671 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x672 = x670 - x656;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x673 = x671 - x657;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x674 = x672 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x675 = x672 * x674;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x675 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x672 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x671 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x676 = x657 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x677 = x657 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x678 = x676 * x677;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x678 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x679 = x4 - x672;
    if (x679 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x680 = x673 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x681 = x673 * x680;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x682 = x673 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x683 = x681 * x682;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x683 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x684 = args[2][48 * steps + ((cycle - 0) & mask)];
    assert(x684 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x685 = args[2][49 * steps + ((cycle - 0) & mask)];
    assert(x685 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x686 = x684 - x670;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x687 = x685 - x671;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x688 = x686 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x689 = x686 * x688;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x689 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x686 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x685 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x690 = x671 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x691 = x671 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x692 = x690 * x691;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x692 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x693 = x4 - x686;
    if (x693 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x694 = x687 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x695 = x687 * x694;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x696 = x687 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x697 = x695 * x696;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x697 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x698 = args[2][50 * steps + ((cycle - 0) & mask)];
    assert(x698 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x699 = args[2][51 * steps + ((cycle - 0) & mask)];
    assert(x699 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x700 = x698 - x684;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x701 = x699 - x685;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x702 = x700 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x703 = x700 * x702;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x703 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x700 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x699 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x704 = x685 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x705 = x685 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x706 = x704 * x705;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x706 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x707 = x4 - x700;
    if (x707 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x708 = x701 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x709 = x701 * x708;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x710 = x701 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x711 = x709 * x710;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x711 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x712 = args[2][52 * steps + ((cycle - 0) & mask)];
    assert(x712 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x713 = args[2][53 * steps + ((cycle - 0) & mask)];
    assert(x713 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x714 = x712 - x698;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x715 = x713 - x699;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x716 = x714 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x717 = x714 * x716;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x717 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x714 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x713 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x718 = x699 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x719 = x699 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x720 = x718 * x719;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x720 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x721 = x4 - x714;
    if (x721 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x722 = x715 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x723 = x715 * x722;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x724 = x715 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x725 = x723 * x724;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x725 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x726 = args[2][54 * steps + ((cycle - 0) & mask)];
    assert(x726 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x727 = args[2][55 * steps + ((cycle - 0) & mask)];
    assert(x727 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x728 = x726 - x712;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x729 = x727 - x713;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x730 = x728 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x731 = x728 * x730;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x731 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x728 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x727 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x732 = x713 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x733 = x713 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x734 = x732 * x733;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x734 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x735 = x4 - x728;
    if (x735 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x736 = x729 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x737 = x729 * x736;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x738 = x729 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x739 = x737 * x738;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x739 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x740 = args[2][56 * steps + ((cycle - 0) & mask)];
    assert(x740 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x741 = args[2][57 * steps + ((cycle - 0) & mask)];
    assert(x741 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x742 = x740 - x726;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x743 = x741 - x727;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x744 = x742 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x745 = x742 * x744;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x745 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x742 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x741 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x746 = x727 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x747 = x727 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x748 = x746 * x747;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x748 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x749 = x4 - x742;
    if (x749 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x750 = x743 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x751 = x743 * x750;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x752 = x743 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x753 = x751 * x752;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x753 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x754 = args[2][58 * steps + ((cycle - 0) & mask)];
    assert(x754 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x755 = args[2][59 * steps + ((cycle - 0) & mask)];
    assert(x755 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x756 = x754 - x740;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x757 = x755 - x741;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x758 = x756 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x759 = x756 * x758;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x759 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x756 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x755 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x760 = x741 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x761 = x741 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x762 = x760 * x761;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x762 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x763 = x4 - x756;
    if (x763 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x764 = x757 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x765 = x757 * x764;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x766 = x757 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x767 = x765 * x766;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x767 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x768 = args[2][60 * steps + ((cycle - 0) & mask)];
    assert(x768 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x769 = args[2][61 * steps + ((cycle - 0) & mask)];
    assert(x769 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x770 = x768 - x754;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x771 = x769 - x755;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x772 = x770 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x773 = x770 * x772;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x773 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x770 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x769 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x774 = x755 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x775 = x755 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x776 = x774 * x775;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x776 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x777 = x4 - x770;
    if (x777 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x778 = x771 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x779 = x771 * x778;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x780 = x771 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x781 = x779 * x780;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x781 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x782 = args[2][62 * steps + ((cycle - 0) & mask)];
    assert(x782 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x783 = args[2][63 * steps + ((cycle - 0) & mask)];
    assert(x783 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x784 = x782 - x768;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x785 = x783 - x769;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x786 = x784 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x787 = x784 * x786;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x787 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x784 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x783 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x788 = x769 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x789 = x769 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x790 = x788 * x789;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x790 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x791 = x4 - x784;
    if (x791 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x792 = x785 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x793 = x785 * x792;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x794 = x785 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x795 = x793 * x794;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x795 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x796 = args[2][64 * steps + ((cycle - 0) & mask)];
    assert(x796 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x797 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x797 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x798 = x796 - x782;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x799 = x797 - x783;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x800 = x798 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x801 = x798 * x800;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x801 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x798 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x797 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x802 = x783 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x803 = x783 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x804 = x802 * x803;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x804 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x805 = x4 - x798;
    if (x805 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x806 = x799 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x807 = x799 * x806;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x808 = x799 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x809 = x807 * x808;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x809 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x810 = args[2][66 * steps + ((cycle - 0) & mask)];
    assert(x810 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x811 = args[2][67 * steps + ((cycle - 0) & mask)];
    assert(x811 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x812 = x810 - x796;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x813 = x811 - x797;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x814 = x812 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x815 = x812 * x814;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x815 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x812 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x811 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x816 = x797 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x817 = x797 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x818 = x816 * x817;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x818 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x819 = x4 - x812;
    if (x819 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x820 = x813 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x821 = x813 * x820;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x822 = x813 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x823 = x821 * x822;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x823 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x824 = args[2][68 * steps + ((cycle - 0) & mask)];
    assert(x824 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x825 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x825 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x826 = x824 - x810;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x827 = x825 - x811;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x828 = x826 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x829 = x826 * x828;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x829 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x826 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x825 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x830 = x811 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x831 = x811 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x832 = x830 * x831;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x832 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x833 = x4 - x826;
    if (x833 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x834 = x827 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x835 = x827 * x834;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x836 = x827 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x837 = x835 * x836;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x837 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x838 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x838 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x839 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x839 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x840 = x838 - x824;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x841 = x839 - x825;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x842 = x840 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x843 = x840 * x842;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x843 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x840 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x839 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x844 = x825 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x845 = x825 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x846 = x844 * x845;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x846 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x847 = x4 - x840;
    if (x847 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x848 = x841 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x849 = x841 * x848;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x850 = x841 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x851 = x849 * x850;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x851 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x852 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x852 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x853 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x853 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x854 = x852 - x838;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x855 = x853 - x839;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x856 = x854 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x857 = x854 * x856;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x857 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x854 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x853 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x858 = x839 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x859 = x839 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x860 = x858 * x859;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x860 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x861 = x4 - x854;
    if (x861 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x862 = x855 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x863 = x855 * x862;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x864 = x855 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x865 = x863 * x864;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x865 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
  }
  if (x8 != 0) {
    {
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x866 = host_outs.at(0);
      auto x867 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][42 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x866);
        reg = x866;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][43 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x867);
        reg = x867;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x868 = host_outs.at(0);
      auto x869 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][44 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x868);
        reg = x868;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][45 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x869);
        reg = x869;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x870 = host_outs.at(0);
      auto x871 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][46 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x870);
        reg = x870;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][47 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x871);
        reg = x871;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x872 = host_outs.at(0);
      auto x873 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][48 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x872);
        reg = x872;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][49 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x873);
        reg = x873;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x874 = host_outs.at(0);
      auto x875 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x874);
        reg = x874;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x875);
        reg = x875;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x876 = host_outs.at(0);
      auto x877 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x876);
        reg = x876;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x877);
        reg = x877;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x878 = host_outs.at(0);
      auto x879 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x878);
        reg = x878;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x879);
        reg = x879;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x880 = host_outs.at(0);
      auto x881 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x880);
        reg = x880;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x881);
        reg = x881;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x882 = host_outs.at(0);
      auto x883 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x882);
        reg = x882;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x883);
        reg = x883;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x884 = host_outs.at(0);
      auto x885 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x884);
        reg = x884;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x885);
        reg = x885;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x886 = host_outs.at(0);
      auto x887 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x886);
        reg = x886;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x887);
        reg = x887;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x888 = host_outs.at(0);
      auto x889 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x888);
        reg = x888;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x889);
        reg = x889;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x890 = host_outs.at(0);
      auto x891 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x890);
        reg = x890;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x891);
        reg = x891;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x892 = host_outs.at(0);
      auto x893 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x892);
        reg = x892;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x893);
        reg = x893;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x894 = host_outs.at(0);
      auto x895 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x894);
        reg = x894;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x895);
        reg = x895;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x896 = host_outs.at(0);
      auto x897 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x896);
        reg = x896;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x897);
        reg = x897;
      }
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":59:42))
    auto x898 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x898 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":60:40))
    auto x899 = args[2][1 * steps + ((cycle - 1) & mask)];
    assert(x899 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x900 = args[2][42 * steps + ((cycle - 0) & mask)];
    assert(x900 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x901 = args[2][43 * steps + ((cycle - 0) & mask)];
    assert(x901 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x902 = x900 - x898;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x903 = x901 - x899;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x904 = x902 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x905 = x902 * x904;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x905 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x902 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x901 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x906 = x899 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x907 = x899 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x908 = x906 * x907;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x908 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x909 = x4 - x902;
    if (x909 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x910 = x903 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x911 = x903 * x910;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x912 = x903 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x913 = x911 * x912;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x913 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x914 = args[2][44 * steps + ((cycle - 0) & mask)];
    assert(x914 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x915 = args[2][45 * steps + ((cycle - 0) & mask)];
    assert(x915 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x916 = x914 - x900;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x917 = x915 - x901;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x918 = x916 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x919 = x916 * x918;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x919 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x916 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x915 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x920 = x901 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x921 = x901 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x922 = x920 * x921;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x922 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x923 = x4 - x916;
    if (x923 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x924 = x917 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x925 = x917 * x924;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x926 = x917 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x927 = x925 * x926;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x927 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x928 = args[2][46 * steps + ((cycle - 0) & mask)];
    assert(x928 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x929 = args[2][47 * steps + ((cycle - 0) & mask)];
    assert(x929 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x930 = x928 - x914;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x931 = x929 - x915;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x932 = x930 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x933 = x930 * x932;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x933 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x930 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x929 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x934 = x915 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x935 = x915 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x936 = x934 * x935;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x936 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x937 = x4 - x930;
    if (x937 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x938 = x931 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x939 = x931 * x938;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x940 = x931 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x941 = x939 * x940;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x941 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x942 = args[2][48 * steps + ((cycle - 0) & mask)];
    assert(x942 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x943 = args[2][49 * steps + ((cycle - 0) & mask)];
    assert(x943 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x944 = x942 - x928;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x945 = x943 - x929;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x946 = x944 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x947 = x944 * x946;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x947 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x944 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x943 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x948 = x929 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x949 = x929 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x950 = x948 * x949;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x950 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x951 = x4 - x944;
    if (x951 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x952 = x945 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x953 = x945 * x952;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x954 = x945 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x955 = x953 * x954;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x955 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x956 = args[2][50 * steps + ((cycle - 0) & mask)];
    assert(x956 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x957 = args[2][51 * steps + ((cycle - 0) & mask)];
    assert(x957 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x958 = x956 - x942;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x959 = x957 - x943;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x960 = x958 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x961 = x958 * x960;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x961 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x958 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x957 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x962 = x943 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x963 = x943 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x964 = x962 * x963;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x964 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x965 = x4 - x958;
    if (x965 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x966 = x959 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x967 = x959 * x966;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x968 = x959 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x969 = x967 * x968;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x969 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x970 = args[2][52 * steps + ((cycle - 0) & mask)];
    assert(x970 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x971 = args[2][53 * steps + ((cycle - 0) & mask)];
    assert(x971 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x972 = x970 - x956;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x973 = x971 - x957;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x974 = x972 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x975 = x972 * x974;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x975 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x972 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x971 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x976 = x957 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x977 = x957 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x978 = x976 * x977;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x978 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x979 = x4 - x972;
    if (x979 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x980 = x973 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x981 = x973 * x980;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x982 = x973 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x983 = x981 * x982;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x983 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x984 = args[2][54 * steps + ((cycle - 0) & mask)];
    assert(x984 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x985 = args[2][55 * steps + ((cycle - 0) & mask)];
    assert(x985 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x986 = x984 - x970;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x987 = x985 - x971;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x988 = x986 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x989 = x986 * x988;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x989 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x986 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x985 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x990 = x971 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x991 = x971 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x992 = x990 * x991;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x992 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x993 = x4 - x986;
    if (x993 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x994 = x987 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x995 = x987 * x994;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x996 = x987 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x997 = x995 * x996;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x997 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x998 = args[2][56 * steps + ((cycle - 0) & mask)];
    assert(x998 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x999 = args[2][57 * steps + ((cycle - 0) & mask)];
    assert(x999 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x1000 = x998 - x984;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x1001 = x999 - x985;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x1002 = x1000 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x1003 = x1000 * x1002;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x1003 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x1000 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x999 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x1004 = x985 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x1005 = x985 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x1006 = x1004 * x1005;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x1006 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x1007 = x4 - x1000;
    if (x1007 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x1008 = x1001 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1009 = x1001 * x1008;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x1010 = x1001 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1011 = x1009 * x1010;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x1011 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1012 = args[2][58 * steps + ((cycle - 0) & mask)];
    assert(x1012 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1013 = args[2][59 * steps + ((cycle - 0) & mask)];
    assert(x1013 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x1014 = x1012 - x998;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x1015 = x1013 - x999;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x1016 = x1014 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x1017 = x1014 * x1016;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x1017 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x1014 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x1013 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x1018 = x999 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x1019 = x999 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x1020 = x1018 * x1019;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x1020 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x1021 = x4 - x1014;
    if (x1021 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x1022 = x1015 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1023 = x1015 * x1022;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x1024 = x1015 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1025 = x1023 * x1024;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x1025 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1026 = args[2][60 * steps + ((cycle - 0) & mask)];
    assert(x1026 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1027 = args[2][61 * steps + ((cycle - 0) & mask)];
    assert(x1027 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x1028 = x1026 - x1012;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x1029 = x1027 - x1013;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x1030 = x1028 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x1031 = x1028 * x1030;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x1031 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x1028 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x1027 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x1032 = x1013 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x1033 = x1013 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x1034 = x1032 * x1033;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x1034 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x1035 = x4 - x1028;
    if (x1035 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x1036 = x1029 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1037 = x1029 * x1036;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x1038 = x1029 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1039 = x1037 * x1038;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x1039 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1040 = args[2][62 * steps + ((cycle - 0) & mask)];
    assert(x1040 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1041 = args[2][63 * steps + ((cycle - 0) & mask)];
    assert(x1041 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x1042 = x1040 - x1026;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x1043 = x1041 - x1027;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x1044 = x1042 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x1045 = x1042 * x1044;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x1045 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x1042 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x1041 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x1046 = x1027 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x1047 = x1027 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x1048 = x1046 * x1047;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x1048 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x1049 = x4 - x1042;
    if (x1049 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x1050 = x1043 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1051 = x1043 * x1050;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x1052 = x1043 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1053 = x1051 * x1052;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x1053 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1054 = args[2][64 * steps + ((cycle - 0) & mask)];
    assert(x1054 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1055 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x1055 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x1056 = x1054 - x1040;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x1057 = x1055 - x1041;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x1058 = x1056 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x1059 = x1056 * x1058;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x1059 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x1056 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x1055 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x1060 = x1041 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x1061 = x1041 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x1062 = x1060 * x1061;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x1062 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x1063 = x4 - x1056;
    if (x1063 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x1064 = x1057 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1065 = x1057 * x1064;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x1066 = x1057 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1067 = x1065 * x1066;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x1067 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1068 = args[2][66 * steps + ((cycle - 0) & mask)];
    assert(x1068 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1069 = args[2][67 * steps + ((cycle - 0) & mask)];
    assert(x1069 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x1070 = x1068 - x1054;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x1071 = x1069 - x1055;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x1072 = x1070 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x1073 = x1070 * x1072;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x1073 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x1070 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x1069 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x1074 = x1055 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x1075 = x1055 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x1076 = x1074 * x1075;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x1076 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x1077 = x4 - x1070;
    if (x1077 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x1078 = x1071 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1079 = x1071 * x1078;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x1080 = x1071 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1081 = x1079 * x1080;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x1081 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1082 = args[2][68 * steps + ((cycle - 0) & mask)];
    assert(x1082 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1083 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x1083 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x1084 = x1082 - x1068;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x1085 = x1083 - x1069;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x1086 = x1084 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x1087 = x1084 * x1086;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x1087 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x1084 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x1083 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x1088 = x1069 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x1089 = x1069 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x1090 = x1088 * x1089;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x1090 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x1091 = x4 - x1084;
    if (x1091 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x1092 = x1085 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1093 = x1085 * x1092;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x1094 = x1085 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1095 = x1093 * x1094;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x1095 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1096 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x1096 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1097 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x1097 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x1098 = x1096 - x1082;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x1099 = x1097 - x1083;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x1100 = x1098 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x1101 = x1098 * x1100;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x1101 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x1098 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x1097 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x1102 = x1083 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x1103 = x1083 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x1104 = x1102 * x1103;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x1104 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x1105 = x4 - x1098;
    if (x1105 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x1106 = x1099 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1107 = x1099 * x1106;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x1108 = x1099 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1109 = x1107 * x1108;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x1109 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1110 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x1110 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1111 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x1111 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x1112 = x1110 - x1096;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x1113 = x1111 - x1097;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x1114 = x1112 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x1115 = x1112 * x1114;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x1115 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x1112 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x1111 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x1116 = x1097 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x1117 = x1097 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x1118 = x1116 * x1117;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x1118 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x1119 = x4 - x1112;
    if (x1119 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x1120 = x1113 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1121 = x1113 * x1120;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x1122 = x1113 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1123 = x1121 * x1122;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x1123 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
  }
  if (x9 != 0) {
    {
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x1124 = host_outs.at(0);
      auto x1125 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][14 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1124);
        reg = x1124;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][15 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1125);
        reg = x1125;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x1126 = host_outs.at(0);
      auto x1127 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:3)
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1126);
        reg = x1126;
      }
      // loc("cirgen/components/bytes.cpp":17:3)
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1127);
        reg = x1127;
      }
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":59:42))
    auto x1128 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x1128 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":60:40))
    auto x1129 = args[2][1 * steps + ((cycle - 1) & mask)];
    assert(x1129 != Fp::invalid());
    // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1130 = args[2][14 * steps + ((cycle - 0) & mask)];
    assert(x1130 != Fp::invalid());
    // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1131 = args[2][15 * steps + ((cycle - 0) & mask)];
    assert(x1131 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x1132 = x1130 - x1128;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x1133 = x1131 - x1129;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x1134 = x1132 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x1135 = x1132 * x1134;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x1135 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x1132 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x1131 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x1136 = x1129 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x1137 = x1129 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x1138 = x1136 * x1137;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x1138 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x1139 = x4 - x1132;
    if (x1139 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x1140 = x1133 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1141 = x1133 * x1140;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x1142 = x1133 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1143 = x1141 * x1142;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x1143 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1144 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x1144 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1145 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x1145 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x1146 = x1144 - x1130;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x1147 = x1145 - x1131;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x1148 = x1146 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x1149 = x1146 * x1148;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x1149 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x1146 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x1145 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x1150 = x1131 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x1151 = x1131 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x1152 = x1150 * x1151;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x1152 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x1153 = x4 - x1146;
    if (x1153 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x1154 = x1147 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1155 = x1147 * x1154;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x1156 = x1147 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1157 = x1155 * x1156;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x1157 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
  }
  if (x10 != 0) {
    // loc("cirgen/components/bytes.cpp":26:3)
    {
      auto& reg = args[2][10 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x0);
      reg = x0;
    }
    // loc("cirgen/components/bytes.cpp":27:3)
    {
      auto& reg = args[2][11 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x0);
      reg = x0;
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":59:42))
    auto x1158 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x1158 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":60:40))
    auto x1159 = args[2][1 * steps + ((cycle - 1) & mask)];
    assert(x1159 != Fp::invalid());
    // loc("Top/Mux/6/PlonkFini/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1160 = args[2][10 * steps + ((cycle - 0) & mask)];
    assert(x1160 != Fp::invalid());
    // loc("Top/Mux/6/PlonkFini/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":151:27))
    auto x1161 = args[2][11 * steps + ((cycle - 0) & mask)];
    assert(x1161 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":63:18)
    auto x1162 = x1160 - x1158;
    // loc("cirgen/components/bytes.cpp":64:17)
    auto x1163 = x1161 - x1159;
    // loc("cirgen/components/bytes.cpp":66:19)
    auto x1164 = x1162 - x4;
    // loc("cirgen/components/bytes.cpp":66:7)
    auto x1165 = x1162 * x1164;
    // loc("cirgen/components/bytes.cpp":66:7)
    if (x1165 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:66");
    if (x1162 != 0) {
      // loc("cirgen/components/bytes.cpp":70:9)
      if (x1161 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:70");
      // loc("cirgen/components/bytes.cpp":72:10)
      auto x1166 = x1159 - x0;
      // loc("cirgen/components/bytes.cpp":72:27)
      auto x1167 = x1159 - x2;
      // loc("cirgen/components/bytes.cpp":72:9)
      auto x1168 = x1166 * x1167;
      // loc("cirgen/components/bytes.cpp":72:9)
      if (x1168 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:72");
    }
    // loc("cirgen/components/bytes.cpp":74:18)
    auto x1169 = x4 - x1162;
    if (x1169 != 0) {
      // loc("cirgen/components/bytes.cpp":76:20)
      auto x1170 = x1163 - x4;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1171 = x1163 * x1170;
      // loc("cirgen/components/bytes.cpp":76:36)
      auto x1172 = x1163 - x1;
      // loc("cirgen/components/bytes.cpp":76:9)
      auto x1173 = x1171 * x1172;
      // loc("cirgen/components/bytes.cpp":76:9)
      if (x1173 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:76");
    }
  }
  return x3;
}

} // namespace risc0::circuit::rv32im
// clang-format on
