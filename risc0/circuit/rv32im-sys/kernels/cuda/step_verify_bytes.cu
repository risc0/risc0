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

#include "extern.cuh"

__device__ void step_verify_bytes(
    void* ctx, uint32_t steps, uint32_t cycle, Fp* arg0, Fp* arg1, Fp* arg2, Fp* arg3, Fp* arg4) {
  uint32_t mask = steps - 1;
  Fp extern_args[96];
  Fp extern_outs[32];
  // loc(unknown)
  Fp x0(255);
  // loc(unknown)
  Fp x1(2);
  // loc(unknown)
  Fp x2(254);
  // loc(unknown)
  Fp x3(0);
  // loc(unknown)
  Fp x4(1);
  // loc("Top/Code/OneHot/hot[1](Reg)"("./zirgen/components/mux.h":49:25))
  auto x5 = arg0[2 * steps + ((cycle - 0) & mask)];
  assert(x5 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[3](Reg)"("./zirgen/components/mux.h":49:25))
  auto x6 = arg0[4 * steps + ((cycle - 0) & mask)];
  assert(x6 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[4](Reg)"("./zirgen/components/mux.h":49:25))
  auto x7 = arg0[5 * steps + ((cycle - 0) & mask)];
  assert(x7 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[5](Reg)"("./zirgen/components/mux.h":49:25))
  auto x8 = arg0[6 * steps + ((cycle - 0) & mask)];
  assert(x8 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[6](Reg)"("./zirgen/components/mux.h":49:25))
  auto x9 = arg0[7 * steps + ((cycle - 0) & mask)];
  assert(x9 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[7](Reg)"("./zirgen/components/mux.h":49:25))
  auto x10 = arg0[8 * steps + ((cycle - 0) & mask)];
  assert(x10 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[0](Reg)"("zirgen/circuit/rv32im/v1/edsl/top.cpp":84:27))
  auto x11 = arg0[1 * steps + ((cycle - 0) & mask)];
  assert(x11 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[2](Reg)"("zirgen/circuit/rv32im/v1/edsl/top.cpp":84:27))
  auto x12 = arg0[3 * steps + ((cycle - 0) & mask)];
  assert(x12 != Fp::invalid());
  if (x11 != 0) {
    // loc("zirgen/components/bytes.cpp":21:3)
    {
      auto& reg = arg2[0 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x3);
      reg = x3;
    }
    // loc("zirgen/components/bytes.cpp":22:3)
    {
      auto& reg = arg2[1 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x3);
      reg = x3;
    }
  }
  if (x5 != 0) {
    {
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x13 = extern_outs[0];
      auto x14 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[45 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x13);
        reg = x13;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[46 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x14);
        reg = x14;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x15 = extern_outs[0];
      auto x16 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[47 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x15);
        reg = x15;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[48 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x16);
        reg = x16;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x17 = extern_outs[0];
      auto x18 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[49 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x17);
        reg = x17;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x18);
        reg = x18;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x19 = extern_outs[0];
      auto x20 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x19);
        reg = x19;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x20);
        reg = x20;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x21 = extern_outs[0];
      auto x22 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x21);
        reg = x21;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x22);
        reg = x22;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x23 = extern_outs[0];
      auto x24 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x23);
        reg = x23;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x24);
        reg = x24;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x25 = extern_outs[0];
      auto x26 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x25);
        reg = x25;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x26);
        reg = x26;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x27 = extern_outs[0];
      auto x28 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x27);
        reg = x27;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x28);
        reg = x28;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x29 = extern_outs[0];
      auto x30 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x29);
        reg = x29;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x30);
        reg = x30;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x31 = extern_outs[0];
      auto x32 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x31);
        reg = x31;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x32);
        reg = x32;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x33 = extern_outs[0];
      auto x34 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x33);
        reg = x33;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x34);
        reg = x34;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x35 = extern_outs[0];
      auto x36 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x35);
        reg = x35;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x36);
        reg = x36;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x37 = extern_outs[0];
      auto x38 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x37);
        reg = x37;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x38);
        reg = x38;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x39 = extern_outs[0];
      auto x40 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x39);
        reg = x39;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x40);
        reg = x40;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x41 = extern_outs[0];
      auto x42 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[73 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x41);
        reg = x41;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x42);
        reg = x42;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x43 = extern_outs[0];
      auto x44 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x43);
        reg = x43;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x44);
        reg = x44;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x45 = extern_outs[0];
      auto x46 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x45);
        reg = x45;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[78 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x46);
        reg = x46;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x47 = extern_outs[0];
      auto x48 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[79 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x47);
        reg = x47;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[80 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x48);
        reg = x48;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x49 = extern_outs[0];
      auto x50 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[81 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x49);
        reg = x49;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[82 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x50);
        reg = x50;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x51 = extern_outs[0];
      auto x52 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[83 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x51);
        reg = x51;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[84 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x52);
        reg = x52;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x53 = extern_outs[0];
      auto x54 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x53);
        reg = x53;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x54);
        reg = x54;
      }
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x55 = arg2[45 * steps + ((cycle - 0) & mask)];
    assert(x55 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x56 = arg2[46 * steps + ((cycle - 0) & mask)];
    assert(x56 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("zirgen/components/bytes.cpp":62:42))
    auto x57 = arg2[0 * steps + ((cycle - 1) & mask)];
    assert(x57 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("zirgen/components/bytes.cpp":63:40))
    auto x58 = arg2[1 * steps + ((cycle - 1) & mask)];
    assert(x58 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x59 = x56 - x58;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x60 = x55 - x57;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x61 = x60 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x62 = x60 * x61;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x62 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x60 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x56 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x63 = x58 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x64 = x58 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x65 = x63 * x64;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x65 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x66 = x4 - x60;
    if (x66 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x67 = x59 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x68 = x59 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x69 = x59 * x67;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x70 = x69 * x68;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x70 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x71 = arg2[47 * steps + ((cycle - 0) & mask)];
    assert(x71 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x72 = arg2[48 * steps + ((cycle - 0) & mask)];
    assert(x72 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x73 = x72 - x56;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x74 = x71 - x55;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x75 = x74 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x76 = x74 * x75;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x76 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x74 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x72 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x77 = x56 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x78 = x56 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x79 = x77 * x78;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x79 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x80 = x4 - x74;
    if (x80 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x81 = x73 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x82 = x73 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x83 = x73 * x81;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x84 = x83 * x82;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x84 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x85 = arg2[49 * steps + ((cycle - 0) & mask)];
    assert(x85 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x86 = arg2[50 * steps + ((cycle - 0) & mask)];
    assert(x86 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x87 = x86 - x72;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x88 = x85 - x71;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x89 = x88 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x90 = x88 * x89;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x90 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x88 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x86 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x91 = x72 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x92 = x72 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x93 = x91 * x92;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x93 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x94 = x4 - x88;
    if (x94 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x95 = x87 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x96 = x87 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x97 = x87 * x95;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x98 = x97 * x96;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x98 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x99 = arg2[51 * steps + ((cycle - 0) & mask)];
    assert(x99 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x100 = arg2[52 * steps + ((cycle - 0) & mask)];
    assert(x100 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x101 = x100 - x86;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x102 = x99 - x85;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x103 = x102 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x104 = x102 * x103;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x104 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x102 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x100 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x105 = x86 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x106 = x86 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x107 = x105 * x106;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x107 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x108 = x4 - x102;
    if (x108 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x109 = x101 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x110 = x101 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x111 = x101 * x109;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x112 = x111 * x110;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x112 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x113 = arg2[53 * steps + ((cycle - 0) & mask)];
    assert(x113 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x114 = arg2[54 * steps + ((cycle - 0) & mask)];
    assert(x114 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x115 = x114 - x100;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x116 = x113 - x99;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x117 = x116 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x118 = x116 * x117;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x118 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x116 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x114 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x119 = x100 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x120 = x100 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x121 = x119 * x120;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x121 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x122 = x4 - x116;
    if (x122 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x123 = x115 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x124 = x115 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x125 = x115 * x123;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x126 = x125 * x124;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x126 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x127 = arg2[55 * steps + ((cycle - 0) & mask)];
    assert(x127 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x128 = arg2[56 * steps + ((cycle - 0) & mask)];
    assert(x128 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x129 = x128 - x114;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x130 = x127 - x113;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x131 = x130 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x132 = x130 * x131;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x132 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x130 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x128 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x133 = x114 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x134 = x114 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x135 = x133 * x134;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x135 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x136 = x4 - x130;
    if (x136 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x137 = x129 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x138 = x129 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x139 = x129 * x137;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x140 = x139 * x138;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x140 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x141 = arg2[57 * steps + ((cycle - 0) & mask)];
    assert(x141 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x142 = arg2[58 * steps + ((cycle - 0) & mask)];
    assert(x142 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x143 = x142 - x128;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x144 = x141 - x127;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x145 = x144 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x146 = x144 * x145;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x146 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x144 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x142 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x147 = x128 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x148 = x128 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x149 = x147 * x148;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x149 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x150 = x4 - x144;
    if (x150 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x151 = x143 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x152 = x143 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x153 = x143 * x151;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x154 = x153 * x152;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x154 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x155 = arg2[59 * steps + ((cycle - 0) & mask)];
    assert(x155 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x156 = arg2[60 * steps + ((cycle - 0) & mask)];
    assert(x156 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x157 = x156 - x142;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x158 = x155 - x141;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x159 = x158 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x160 = x158 * x159;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x160 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x158 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x156 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x161 = x142 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x162 = x142 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x163 = x161 * x162;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x163 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x164 = x4 - x158;
    if (x164 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x165 = x157 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x166 = x157 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x167 = x157 * x165;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x168 = x167 * x166;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x168 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x169 = arg2[61 * steps + ((cycle - 0) & mask)];
    assert(x169 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x170 = arg2[62 * steps + ((cycle - 0) & mask)];
    assert(x170 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x171 = x170 - x156;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x172 = x169 - x155;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x173 = x172 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x174 = x172 * x173;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x174 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x172 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x170 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x175 = x156 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x176 = x156 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x177 = x175 * x176;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x177 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x178 = x4 - x172;
    if (x178 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x179 = x171 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x180 = x171 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x181 = x171 * x179;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x182 = x181 * x180;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x182 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x183 = arg2[63 * steps + ((cycle - 0) & mask)];
    assert(x183 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x184 = arg2[64 * steps + ((cycle - 0) & mask)];
    assert(x184 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x185 = x184 - x170;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x186 = x183 - x169;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x187 = x186 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x188 = x186 * x187;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x188 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x186 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x184 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x189 = x170 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x190 = x170 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x191 = x189 * x190;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x191 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x192 = x4 - x186;
    if (x192 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x193 = x185 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x194 = x185 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x195 = x185 * x193;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x196 = x195 * x194;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x196 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x197 = arg2[65 * steps + ((cycle - 0) & mask)];
    assert(x197 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x198 = arg2[66 * steps + ((cycle - 0) & mask)];
    assert(x198 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x199 = x198 - x184;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x200 = x197 - x183;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x201 = x200 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x202 = x200 * x201;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x202 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x200 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x198 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x203 = x184 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x204 = x184 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x205 = x203 * x204;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x205 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x206 = x4 - x200;
    if (x206 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x207 = x199 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x208 = x199 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x209 = x199 * x207;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x210 = x209 * x208;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x210 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x211 = arg2[67 * steps + ((cycle - 0) & mask)];
    assert(x211 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x212 = arg2[68 * steps + ((cycle - 0) & mask)];
    assert(x212 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x213 = x212 - x198;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x214 = x211 - x197;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x215 = x214 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x216 = x214 * x215;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x216 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x214 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x212 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x217 = x198 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x218 = x198 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x219 = x217 * x218;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x219 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x220 = x4 - x214;
    if (x220 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x221 = x213 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x222 = x213 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x223 = x213 * x221;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x224 = x223 * x222;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x224 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x225 = arg2[69 * steps + ((cycle - 0) & mask)];
    assert(x225 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x226 = arg2[70 * steps + ((cycle - 0) & mask)];
    assert(x226 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x227 = x226 - x212;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x228 = x225 - x211;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x229 = x228 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x230 = x228 * x229;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x230 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x228 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x226 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x231 = x212 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x232 = x212 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x233 = x231 * x232;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x233 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x234 = x4 - x228;
    if (x234 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x235 = x227 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x236 = x227 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x237 = x227 * x235;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x238 = x237 * x236;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x238 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x239 = arg2[71 * steps + ((cycle - 0) & mask)];
    assert(x239 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x240 = arg2[72 * steps + ((cycle - 0) & mask)];
    assert(x240 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x241 = x240 - x226;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x242 = x239 - x225;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x243 = x242 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x244 = x242 * x243;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x244 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x242 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x240 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x245 = x226 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x246 = x226 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x247 = x245 * x246;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x247 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x248 = x4 - x242;
    if (x248 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x249 = x241 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x250 = x241 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x251 = x241 * x249;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x252 = x251 * x250;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x252 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x253 = arg2[73 * steps + ((cycle - 0) & mask)];
    assert(x253 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x254 = arg2[74 * steps + ((cycle - 0) & mask)];
    assert(x254 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x255 = x254 - x240;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x256 = x253 - x239;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x257 = x256 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x258 = x256 * x257;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x258 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x256 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x254 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x259 = x240 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x260 = x240 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x261 = x259 * x260;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x261 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x262 = x4 - x256;
    if (x262 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x263 = x255 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x264 = x255 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x265 = x255 * x263;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x266 = x265 * x264;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x266 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x267 = arg2[75 * steps + ((cycle - 0) & mask)];
    assert(x267 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x268 = arg2[76 * steps + ((cycle - 0) & mask)];
    assert(x268 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x269 = x268 - x254;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x270 = x267 - x253;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x271 = x270 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x272 = x270 * x271;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x272 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x270 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x268 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x273 = x254 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x274 = x254 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x275 = x273 * x274;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x275 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x276 = x4 - x270;
    if (x276 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x277 = x269 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x278 = x269 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x279 = x269 * x277;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x280 = x279 * x278;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x280 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x281 = arg2[77 * steps + ((cycle - 0) & mask)];
    assert(x281 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x282 = arg2[78 * steps + ((cycle - 0) & mask)];
    assert(x282 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x283 = x282 - x268;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x284 = x281 - x267;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x285 = x284 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x286 = x284 * x285;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x286 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x284 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x282 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x287 = x268 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x288 = x268 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x289 = x287 * x288;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x289 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x290 = x4 - x284;
    if (x290 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x291 = x283 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x292 = x283 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x293 = x283 * x291;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x294 = x293 * x292;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x294 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x295 = arg2[79 * steps + ((cycle - 0) & mask)];
    assert(x295 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x296 = arg2[80 * steps + ((cycle - 0) & mask)];
    assert(x296 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x297 = x296 - x282;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x298 = x295 - x281;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x299 = x298 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x300 = x298 * x299;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x300 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x298 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x296 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x301 = x282 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x302 = x282 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x303 = x301 * x302;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x303 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x304 = x4 - x298;
    if (x304 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x305 = x297 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x306 = x297 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x307 = x297 * x305;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x308 = x307 * x306;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x308 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x309 = arg2[81 * steps + ((cycle - 0) & mask)];
    assert(x309 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x310 = arg2[82 * steps + ((cycle - 0) & mask)];
    assert(x310 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x311 = x310 - x296;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x312 = x309 - x295;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x313 = x312 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x314 = x312 * x313;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x314 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x312 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x310 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x315 = x296 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x316 = x296 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x317 = x315 * x316;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x317 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x318 = x4 - x312;
    if (x318 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x319 = x311 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x320 = x311 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x321 = x311 * x319;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x322 = x321 * x320;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x322 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x323 = arg2[83 * steps + ((cycle - 0) & mask)];
    assert(x323 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x324 = arg2[84 * steps + ((cycle - 0) & mask)];
    assert(x324 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x325 = x324 - x310;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x326 = x323 - x309;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x327 = x326 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x328 = x326 * x327;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x328 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x326 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x324 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x329 = x310 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x330 = x310 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x331 = x329 * x330;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x331 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x332 = x4 - x326;
    if (x332 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x333 = x325 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x334 = x325 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x335 = x325 * x333;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x336 = x335 * x334;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x336 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x337 = arg2[0 * steps + ((cycle - 0) & mask)];
    assert(x337 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x338 = arg2[1 * steps + ((cycle - 0) & mask)];
    assert(x338 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x339 = x338 - x324;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x340 = x337 - x323;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x341 = x340 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x342 = x340 * x341;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x342 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x340 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x338 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x343 = x324 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x344 = x324 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x345 = x343 * x344;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x345 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x346 = x4 - x340;
    if (x346 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x347 = x339 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x348 = x339 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x349 = x339 * x347;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x350 = x349 * x348;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x350 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
  }
  if (x12 != 0) {
    {
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x351 = extern_outs[0];
      auto x352 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[37 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x351);
        reg = x351;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[38 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x352);
        reg = x352;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x353 = extern_outs[0];
      auto x354 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[39 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x353);
        reg = x353;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[40 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x354);
        reg = x354;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x355 = extern_outs[0];
      auto x356 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[41 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x355);
        reg = x355;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[42 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x356);
        reg = x356;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x357 = extern_outs[0];
      auto x358 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[43 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x357);
        reg = x357;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[44 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x358);
        reg = x358;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x359 = extern_outs[0];
      auto x360 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[45 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x359);
        reg = x359;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[46 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x360);
        reg = x360;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x361 = extern_outs[0];
      auto x362 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[47 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x361);
        reg = x361;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[48 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x362);
        reg = x362;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x363 = extern_outs[0];
      auto x364 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[49 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x363);
        reg = x363;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x364);
        reg = x364;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x365 = extern_outs[0];
      auto x366 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x365);
        reg = x365;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x366);
        reg = x366;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x367 = extern_outs[0];
      auto x368 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x367);
        reg = x367;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x368);
        reg = x368;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x369 = extern_outs[0];
      auto x370 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x369);
        reg = x369;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x370);
        reg = x370;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x371 = extern_outs[0];
      auto x372 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x371);
        reg = x371;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x372);
        reg = x372;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x373 = extern_outs[0];
      auto x374 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x373);
        reg = x373;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x374);
        reg = x374;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x375 = extern_outs[0];
      auto x376 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x375);
        reg = x375;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x376);
        reg = x376;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x377 = extern_outs[0];
      auto x378 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x377);
        reg = x377;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x378);
        reg = x378;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x379 = extern_outs[0];
      auto x380 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x379);
        reg = x379;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x380);
        reg = x380;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x381 = extern_outs[0];
      auto x382 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x381);
        reg = x381;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x382);
        reg = x382;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x383 = extern_outs[0];
      auto x384 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x383);
        reg = x383;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x384);
        reg = x384;
      }
    }
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x385 = arg2[37 * steps + ((cycle - 0) & mask)];
    assert(x385 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x386 = arg2[38 * steps + ((cycle - 0) & mask)];
    assert(x386 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("zirgen/components/bytes.cpp":62:42))
    auto x387 = arg2[0 * steps + ((cycle - 1) & mask)];
    assert(x387 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("zirgen/components/bytes.cpp":63:40))
    auto x388 = arg2[1 * steps + ((cycle - 1) & mask)];
    assert(x388 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x389 = x386 - x388;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x390 = x385 - x387;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x391 = x390 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x392 = x390 * x391;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x392 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x390 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x386 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x393 = x388 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x394 = x388 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x395 = x393 * x394;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x395 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x396 = x4 - x390;
    if (x396 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x397 = x389 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x398 = x389 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x399 = x389 * x397;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x400 = x399 * x398;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x400 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x401 = arg2[39 * steps + ((cycle - 0) & mask)];
    assert(x401 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x402 = arg2[40 * steps + ((cycle - 0) & mask)];
    assert(x402 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x403 = x402 - x386;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x404 = x401 - x385;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x405 = x404 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x406 = x404 * x405;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x406 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x404 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x402 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x407 = x386 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x408 = x386 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x409 = x407 * x408;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x409 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x410 = x4 - x404;
    if (x410 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x411 = x403 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x412 = x403 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x413 = x403 * x411;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x414 = x413 * x412;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x414 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x415 = arg2[41 * steps + ((cycle - 0) & mask)];
    assert(x415 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x416 = arg2[42 * steps + ((cycle - 0) & mask)];
    assert(x416 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x417 = x416 - x402;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x418 = x415 - x401;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x419 = x418 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x420 = x418 * x419;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x420 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x418 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x416 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x421 = x402 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x422 = x402 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x423 = x421 * x422;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x423 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x424 = x4 - x418;
    if (x424 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x425 = x417 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x426 = x417 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x427 = x417 * x425;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x428 = x427 * x426;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x428 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x429 = arg2[43 * steps + ((cycle - 0) & mask)];
    assert(x429 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x430 = arg2[44 * steps + ((cycle - 0) & mask)];
    assert(x430 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x431 = x430 - x416;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x432 = x429 - x415;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x433 = x432 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x434 = x432 * x433;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x434 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x432 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x430 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x435 = x416 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x436 = x416 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x437 = x435 * x436;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x437 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x438 = x4 - x432;
    if (x438 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x439 = x431 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x440 = x431 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x441 = x431 * x439;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x442 = x441 * x440;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x442 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x443 = arg2[45 * steps + ((cycle - 0) & mask)];
    assert(x443 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x444 = arg2[46 * steps + ((cycle - 0) & mask)];
    assert(x444 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x445 = x444 - x430;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x446 = x443 - x429;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x447 = x446 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x448 = x446 * x447;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x448 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x446 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x444 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x449 = x430 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x450 = x430 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x451 = x449 * x450;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x451 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x452 = x4 - x446;
    if (x452 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x453 = x445 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x454 = x445 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x455 = x445 * x453;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x456 = x455 * x454;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x456 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x457 = arg2[47 * steps + ((cycle - 0) & mask)];
    assert(x457 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x458 = arg2[48 * steps + ((cycle - 0) & mask)];
    assert(x458 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x459 = x458 - x444;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x460 = x457 - x443;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x461 = x460 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x462 = x460 * x461;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x462 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x460 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x458 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x463 = x444 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x464 = x444 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x465 = x463 * x464;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x465 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x466 = x4 - x460;
    if (x466 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x467 = x459 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x468 = x459 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x469 = x459 * x467;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x470 = x469 * x468;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x470 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x471 = arg2[49 * steps + ((cycle - 0) & mask)];
    assert(x471 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x472 = arg2[50 * steps + ((cycle - 0) & mask)];
    assert(x472 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x473 = x472 - x458;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x474 = x471 - x457;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x475 = x474 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x476 = x474 * x475;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x476 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x474 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x472 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x477 = x458 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x478 = x458 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x479 = x477 * x478;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x479 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x480 = x4 - x474;
    if (x480 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x481 = x473 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x482 = x473 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x483 = x473 * x481;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x484 = x483 * x482;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x484 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x485 = arg2[51 * steps + ((cycle - 0) & mask)];
    assert(x485 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x486 = arg2[52 * steps + ((cycle - 0) & mask)];
    assert(x486 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x487 = x486 - x472;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x488 = x485 - x471;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x489 = x488 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x490 = x488 * x489;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x490 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x488 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x486 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x491 = x472 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x492 = x472 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x493 = x491 * x492;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x493 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x494 = x4 - x488;
    if (x494 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x495 = x487 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x496 = x487 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x497 = x487 * x495;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x498 = x497 * x496;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x498 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x499 = arg2[53 * steps + ((cycle - 0) & mask)];
    assert(x499 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x500 = arg2[54 * steps + ((cycle - 0) & mask)];
    assert(x500 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x501 = x500 - x486;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x502 = x499 - x485;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x503 = x502 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x504 = x502 * x503;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x504 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x502 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x500 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x505 = x486 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x506 = x486 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x507 = x505 * x506;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x507 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x508 = x4 - x502;
    if (x508 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x509 = x501 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x510 = x501 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x511 = x501 * x509;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x512 = x511 * x510;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x512 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x513 = arg2[55 * steps + ((cycle - 0) & mask)];
    assert(x513 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x514 = arg2[56 * steps + ((cycle - 0) & mask)];
    assert(x514 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x515 = x514 - x500;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x516 = x513 - x499;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x517 = x516 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x518 = x516 * x517;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x518 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x516 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x514 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x519 = x500 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x520 = x500 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x521 = x519 * x520;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x521 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x522 = x4 - x516;
    if (x522 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x523 = x515 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x524 = x515 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x525 = x515 * x523;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x526 = x525 * x524;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x526 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x527 = arg2[57 * steps + ((cycle - 0) & mask)];
    assert(x527 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x528 = arg2[58 * steps + ((cycle - 0) & mask)];
    assert(x528 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x529 = x528 - x514;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x530 = x527 - x513;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x531 = x530 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x532 = x530 * x531;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x532 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x530 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x528 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x533 = x514 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x534 = x514 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x535 = x533 * x534;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x535 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x536 = x4 - x530;
    if (x536 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x537 = x529 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x538 = x529 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x539 = x529 * x537;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x540 = x539 * x538;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x540 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x541 = arg2[59 * steps + ((cycle - 0) & mask)];
    assert(x541 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x542 = arg2[60 * steps + ((cycle - 0) & mask)];
    assert(x542 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x543 = x542 - x528;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x544 = x541 - x527;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x545 = x544 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x546 = x544 * x545;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x546 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x544 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x542 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x547 = x528 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x548 = x528 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x549 = x547 * x548;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x549 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x550 = x4 - x544;
    if (x550 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x551 = x543 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x552 = x543 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x553 = x543 * x551;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x554 = x553 * x552;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x554 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x555 = arg2[61 * steps + ((cycle - 0) & mask)];
    assert(x555 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x556 = arg2[62 * steps + ((cycle - 0) & mask)];
    assert(x556 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x557 = x556 - x542;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x558 = x555 - x541;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x559 = x558 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x560 = x558 * x559;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x560 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x558 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x556 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x561 = x542 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x562 = x542 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x563 = x561 * x562;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x563 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x564 = x4 - x558;
    if (x564 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x565 = x557 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x566 = x557 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x567 = x557 * x565;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x568 = x567 * x566;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x568 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x569 = arg2[63 * steps + ((cycle - 0) & mask)];
    assert(x569 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x570 = arg2[64 * steps + ((cycle - 0) & mask)];
    assert(x570 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x571 = x570 - x556;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x572 = x569 - x555;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x573 = x572 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x574 = x572 * x573;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x574 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x572 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x570 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x575 = x556 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x576 = x556 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x577 = x575 * x576;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x577 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x578 = x4 - x572;
    if (x578 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x579 = x571 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x580 = x571 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x581 = x571 * x579;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x582 = x581 * x580;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x582 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x583 = arg2[65 * steps + ((cycle - 0) & mask)];
    assert(x583 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x584 = arg2[66 * steps + ((cycle - 0) & mask)];
    assert(x584 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x585 = x584 - x570;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x586 = x583 - x569;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x587 = x586 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x588 = x586 * x587;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x588 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x586 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x584 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x589 = x570 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x590 = x570 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x591 = x589 * x590;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x591 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x592 = x4 - x586;
    if (x592 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x593 = x585 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x594 = x585 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x595 = x585 * x593;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x596 = x595 * x594;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x596 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x597 = arg2[67 * steps + ((cycle - 0) & mask)];
    assert(x597 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x598 = arg2[68 * steps + ((cycle - 0) & mask)];
    assert(x598 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x599 = x598 - x584;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x600 = x597 - x583;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x601 = x600 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x602 = x600 * x601;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x602 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x600 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x598 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x603 = x584 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x604 = x584 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x605 = x603 * x604;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x605 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x606 = x4 - x600;
    if (x606 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x607 = x599 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x608 = x599 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x609 = x599 * x607;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x610 = x609 * x608;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x610 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x611 = arg2[0 * steps + ((cycle - 0) & mask)];
    assert(x611 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x612 = arg2[1 * steps + ((cycle - 0) & mask)];
    assert(x612 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x613 = x612 - x598;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x614 = x611 - x597;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x615 = x614 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x616 = x614 * x615;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x616 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x614 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x612 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x617 = x598 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x618 = x598 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x619 = x617 * x618;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x619 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x620 = x4 - x614;
    if (x620 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x621 = x613 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x622 = x613 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x623 = x613 * x621;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x624 = x623 * x622;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x624 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
  }
  if (x6 != 0) {
    {
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x625 = extern_outs[0];
      auto x626 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[37 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x625);
        reg = x625;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[38 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x626);
        reg = x626;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x627 = extern_outs[0];
      auto x628 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[39 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x627);
        reg = x627;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[40 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x628);
        reg = x628;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x629 = extern_outs[0];
      auto x630 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[41 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x629);
        reg = x629;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[42 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x630);
        reg = x630;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x631 = extern_outs[0];
      auto x632 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[43 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x631);
        reg = x631;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[44 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x632);
        reg = x632;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x633 = extern_outs[0];
      auto x634 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[45 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x633);
        reg = x633;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[46 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x634);
        reg = x634;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x635 = extern_outs[0];
      auto x636 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[47 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x635);
        reg = x635;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[48 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x636);
        reg = x636;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x637 = extern_outs[0];
      auto x638 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[49 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x637);
        reg = x637;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x638);
        reg = x638;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x639 = extern_outs[0];
      auto x640 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x639);
        reg = x639;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x640);
        reg = x640;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x641 = extern_outs[0];
      auto x642 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x641);
        reg = x641;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x642);
        reg = x642;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x643 = extern_outs[0];
      auto x644 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x643);
        reg = x643;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x644);
        reg = x644;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x645 = extern_outs[0];
      auto x646 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x645);
        reg = x645;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x646);
        reg = x646;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x647 = extern_outs[0];
      auto x648 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x647);
        reg = x647;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x648);
        reg = x648;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x649 = extern_outs[0];
      auto x650 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x649);
        reg = x649;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x650);
        reg = x650;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x651 = extern_outs[0];
      auto x652 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x651);
        reg = x651;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x652);
        reg = x652;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x653 = extern_outs[0];
      auto x654 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x653);
        reg = x653;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x654);
        reg = x654;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x655 = extern_outs[0];
      auto x656 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x655);
        reg = x655;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x656);
        reg = x656;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x657 = extern_outs[0];
      auto x658 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x657);
        reg = x657;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x658);
        reg = x658;
      }
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x659 = arg2[37 * steps + ((cycle - 0) & mask)];
    assert(x659 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x660 = arg2[38 * steps + ((cycle - 0) & mask)];
    assert(x660 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("zirgen/components/bytes.cpp":62:42))
    auto x661 = arg2[0 * steps + ((cycle - 1) & mask)];
    assert(x661 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("zirgen/components/bytes.cpp":63:40))
    auto x662 = arg2[1 * steps + ((cycle - 1) & mask)];
    assert(x662 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x663 = x660 - x662;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x664 = x659 - x661;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x665 = x664 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x666 = x664 * x665;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x666 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x664 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x660 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x667 = x662 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x668 = x662 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x669 = x667 * x668;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x669 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x670 = x4 - x664;
    if (x670 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x671 = x663 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x672 = x663 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x673 = x663 * x671;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x674 = x673 * x672;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x674 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x675 = arg2[39 * steps + ((cycle - 0) & mask)];
    assert(x675 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x676 = arg2[40 * steps + ((cycle - 0) & mask)];
    assert(x676 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x677 = x676 - x660;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x678 = x675 - x659;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x679 = x678 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x680 = x678 * x679;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x680 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x678 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x676 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x681 = x660 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x682 = x660 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x683 = x681 * x682;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x683 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x684 = x4 - x678;
    if (x684 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x685 = x677 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x686 = x677 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x687 = x677 * x685;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x688 = x687 * x686;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x688 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x689 = arg2[41 * steps + ((cycle - 0) & mask)];
    assert(x689 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x690 = arg2[42 * steps + ((cycle - 0) & mask)];
    assert(x690 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x691 = x690 - x676;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x692 = x689 - x675;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x693 = x692 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x694 = x692 * x693;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x694 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x692 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x690 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x695 = x676 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x696 = x676 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x697 = x695 * x696;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x697 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x698 = x4 - x692;
    if (x698 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x699 = x691 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x700 = x691 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x701 = x691 * x699;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x702 = x701 * x700;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x702 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x703 = arg2[43 * steps + ((cycle - 0) & mask)];
    assert(x703 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x704 = arg2[44 * steps + ((cycle - 0) & mask)];
    assert(x704 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x705 = x704 - x690;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x706 = x703 - x689;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x707 = x706 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x708 = x706 * x707;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x708 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x706 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x704 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x709 = x690 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x710 = x690 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x711 = x709 * x710;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x711 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x712 = x4 - x706;
    if (x712 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x713 = x705 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x714 = x705 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x715 = x705 * x713;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x716 = x715 * x714;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x716 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x717 = arg2[45 * steps + ((cycle - 0) & mask)];
    assert(x717 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x718 = arg2[46 * steps + ((cycle - 0) & mask)];
    assert(x718 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x719 = x718 - x704;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x720 = x717 - x703;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x721 = x720 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x722 = x720 * x721;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x722 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x720 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x718 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x723 = x704 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x724 = x704 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x725 = x723 * x724;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x725 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x726 = x4 - x720;
    if (x726 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x727 = x719 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x728 = x719 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x729 = x719 * x727;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x730 = x729 * x728;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x730 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x731 = arg2[47 * steps + ((cycle - 0) & mask)];
    assert(x731 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x732 = arg2[48 * steps + ((cycle - 0) & mask)];
    assert(x732 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x733 = x732 - x718;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x734 = x731 - x717;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x735 = x734 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x736 = x734 * x735;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x736 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x734 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x732 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x737 = x718 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x738 = x718 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x739 = x737 * x738;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x739 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x740 = x4 - x734;
    if (x740 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x741 = x733 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x742 = x733 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x743 = x733 * x741;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x744 = x743 * x742;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x744 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x745 = arg2[49 * steps + ((cycle - 0) & mask)];
    assert(x745 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x746 = arg2[50 * steps + ((cycle - 0) & mask)];
    assert(x746 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x747 = x746 - x732;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x748 = x745 - x731;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x749 = x748 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x750 = x748 * x749;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x750 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x748 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x746 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x751 = x732 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x752 = x732 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x753 = x751 * x752;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x753 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x754 = x4 - x748;
    if (x754 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x755 = x747 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x756 = x747 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x757 = x747 * x755;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x758 = x757 * x756;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x758 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x759 = arg2[51 * steps + ((cycle - 0) & mask)];
    assert(x759 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x760 = arg2[52 * steps + ((cycle - 0) & mask)];
    assert(x760 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x761 = x760 - x746;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x762 = x759 - x745;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x763 = x762 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x764 = x762 * x763;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x764 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x762 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x760 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x765 = x746 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x766 = x746 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x767 = x765 * x766;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x767 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x768 = x4 - x762;
    if (x768 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x769 = x761 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x770 = x761 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x771 = x761 * x769;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x772 = x771 * x770;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x772 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x773 = arg2[53 * steps + ((cycle - 0) & mask)];
    assert(x773 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x774 = arg2[54 * steps + ((cycle - 0) & mask)];
    assert(x774 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x775 = x774 - x760;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x776 = x773 - x759;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x777 = x776 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x778 = x776 * x777;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x778 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x776 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x774 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x779 = x760 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x780 = x760 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x781 = x779 * x780;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x781 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x782 = x4 - x776;
    if (x782 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x783 = x775 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x784 = x775 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x785 = x775 * x783;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x786 = x785 * x784;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x786 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x787 = arg2[55 * steps + ((cycle - 0) & mask)];
    assert(x787 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x788 = arg2[56 * steps + ((cycle - 0) & mask)];
    assert(x788 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x789 = x788 - x774;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x790 = x787 - x773;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x791 = x790 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x792 = x790 * x791;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x792 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x790 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x788 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x793 = x774 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x794 = x774 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x795 = x793 * x794;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x795 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x796 = x4 - x790;
    if (x796 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x797 = x789 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x798 = x789 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x799 = x789 * x797;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x800 = x799 * x798;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x800 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x801 = arg2[57 * steps + ((cycle - 0) & mask)];
    assert(x801 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x802 = arg2[58 * steps + ((cycle - 0) & mask)];
    assert(x802 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x803 = x802 - x788;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x804 = x801 - x787;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x805 = x804 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x806 = x804 * x805;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x806 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x804 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x802 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x807 = x788 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x808 = x788 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x809 = x807 * x808;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x809 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x810 = x4 - x804;
    if (x810 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x811 = x803 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x812 = x803 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x813 = x803 * x811;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x814 = x813 * x812;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x814 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x815 = arg2[59 * steps + ((cycle - 0) & mask)];
    assert(x815 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x816 = arg2[60 * steps + ((cycle - 0) & mask)];
    assert(x816 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x817 = x816 - x802;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x818 = x815 - x801;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x819 = x818 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x820 = x818 * x819;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x820 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x818 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x816 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x821 = x802 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x822 = x802 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x823 = x821 * x822;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x823 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x824 = x4 - x818;
    if (x824 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x825 = x817 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x826 = x817 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x827 = x817 * x825;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x828 = x827 * x826;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x828 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x829 = arg2[61 * steps + ((cycle - 0) & mask)];
    assert(x829 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x830 = arg2[62 * steps + ((cycle - 0) & mask)];
    assert(x830 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x831 = x830 - x816;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x832 = x829 - x815;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x833 = x832 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x834 = x832 * x833;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x834 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x832 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x830 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x835 = x816 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x836 = x816 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x837 = x835 * x836;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x837 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x838 = x4 - x832;
    if (x838 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x839 = x831 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x840 = x831 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x841 = x831 * x839;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x842 = x841 * x840;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x842 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x843 = arg2[63 * steps + ((cycle - 0) & mask)];
    assert(x843 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x844 = arg2[64 * steps + ((cycle - 0) & mask)];
    assert(x844 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x845 = x844 - x830;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x846 = x843 - x829;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x847 = x846 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x848 = x846 * x847;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x848 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x846 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x844 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x849 = x830 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x850 = x830 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x851 = x849 * x850;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x851 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x852 = x4 - x846;
    if (x852 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x853 = x845 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x854 = x845 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x855 = x845 * x853;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x856 = x855 * x854;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x856 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x857 = arg2[65 * steps + ((cycle - 0) & mask)];
    assert(x857 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x858 = arg2[66 * steps + ((cycle - 0) & mask)];
    assert(x858 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x859 = x858 - x844;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x860 = x857 - x843;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x861 = x860 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x862 = x860 * x861;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x862 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x860 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x858 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x863 = x844 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x864 = x844 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x865 = x863 * x864;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x865 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x866 = x4 - x860;
    if (x866 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x867 = x859 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x868 = x859 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x869 = x859 * x867;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x870 = x869 * x868;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x870 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x871 = arg2[67 * steps + ((cycle - 0) & mask)];
    assert(x871 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x872 = arg2[68 * steps + ((cycle - 0) & mask)];
    assert(x872 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x873 = x872 - x858;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x874 = x871 - x857;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x875 = x874 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x876 = x874 * x875;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x876 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x874 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x872 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x877 = x858 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x878 = x858 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x879 = x877 * x878;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x879 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x880 = x4 - x874;
    if (x880 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x881 = x873 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x882 = x873 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x883 = x873 * x881;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x884 = x883 * x882;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x884 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x885 = arg2[0 * steps + ((cycle - 0) & mask)];
    assert(x885 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x886 = arg2[1 * steps + ((cycle - 0) & mask)];
    assert(x886 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x887 = x886 - x872;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x888 = x885 - x871;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x889 = x888 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x890 = x888 * x889;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x890 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x888 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x886 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x891 = x872 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x892 = x872 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x893 = x891 * x892;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x893 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x894 = x4 - x888;
    if (x894 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x895 = x887 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x896 = x887 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x897 = x887 * x895;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x898 = x897 * x896;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x898 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
  }
  if (x7 != 0) {
    {
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x899 = extern_outs[0];
      auto x900 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[37 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x899);
        reg = x899;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[38 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x900);
        reg = x900;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x901 = extern_outs[0];
      auto x902 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[39 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x901);
        reg = x901;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[40 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x902);
        reg = x902;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x903 = extern_outs[0];
      auto x904 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[41 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x903);
        reg = x903;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[42 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x904);
        reg = x904;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x905 = extern_outs[0];
      auto x906 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[43 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x905);
        reg = x905;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[44 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x906);
        reg = x906;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x907 = extern_outs[0];
      auto x908 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[45 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x907);
        reg = x907;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[46 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x908);
        reg = x908;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x909 = extern_outs[0];
      auto x910 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[47 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x909);
        reg = x909;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[48 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x910);
        reg = x910;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x911 = extern_outs[0];
      auto x912 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[49 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x911);
        reg = x911;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x912);
        reg = x912;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x913 = extern_outs[0];
      auto x914 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x913);
        reg = x913;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x914);
        reg = x914;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x915 = extern_outs[0];
      auto x916 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x915);
        reg = x915;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x916);
        reg = x916;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x917 = extern_outs[0];
      auto x918 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x917);
        reg = x917;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x918);
        reg = x918;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x919 = extern_outs[0];
      auto x920 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x919);
        reg = x919;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x920);
        reg = x920;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x921 = extern_outs[0];
      auto x922 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x921);
        reg = x921;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x922);
        reg = x922;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x923 = extern_outs[0];
      auto x924 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x923);
        reg = x923;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x924);
        reg = x924;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x925 = extern_outs[0];
      auto x926 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x925);
        reg = x925;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x926);
        reg = x926;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x927 = extern_outs[0];
      auto x928 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x927);
        reg = x927;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x928);
        reg = x928;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x929 = extern_outs[0];
      auto x930 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x929);
        reg = x929;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x930);
        reg = x930;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x931 = extern_outs[0];
      auto x932 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x931);
        reg = x931;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x932);
        reg = x932;
      }
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x933 = arg2[37 * steps + ((cycle - 0) & mask)];
    assert(x933 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x934 = arg2[38 * steps + ((cycle - 0) & mask)];
    assert(x934 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("zirgen/components/bytes.cpp":62:42))
    auto x935 = arg2[0 * steps + ((cycle - 1) & mask)];
    assert(x935 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("zirgen/components/bytes.cpp":63:40))
    auto x936 = arg2[1 * steps + ((cycle - 1) & mask)];
    assert(x936 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x937 = x934 - x936;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x938 = x933 - x935;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x939 = x938 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x940 = x938 * x939;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x940 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x938 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x934 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x941 = x936 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x942 = x936 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x943 = x941 * x942;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x943 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x944 = x4 - x938;
    if (x944 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x945 = x937 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x946 = x937 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x947 = x937 * x945;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x948 = x947 * x946;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x948 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x949 = arg2[39 * steps + ((cycle - 0) & mask)];
    assert(x949 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x950 = arg2[40 * steps + ((cycle - 0) & mask)];
    assert(x950 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x951 = x950 - x934;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x952 = x949 - x933;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x953 = x952 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x954 = x952 * x953;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x954 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x952 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x950 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x955 = x934 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x956 = x934 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x957 = x955 * x956;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x957 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x958 = x4 - x952;
    if (x958 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x959 = x951 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x960 = x951 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x961 = x951 * x959;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x962 = x961 * x960;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x962 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x963 = arg2[41 * steps + ((cycle - 0) & mask)];
    assert(x963 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x964 = arg2[42 * steps + ((cycle - 0) & mask)];
    assert(x964 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x965 = x964 - x950;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x966 = x963 - x949;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x967 = x966 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x968 = x966 * x967;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x968 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x966 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x964 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x969 = x950 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x970 = x950 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x971 = x969 * x970;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x971 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x972 = x4 - x966;
    if (x972 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x973 = x965 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x974 = x965 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x975 = x965 * x973;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x976 = x975 * x974;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x976 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x977 = arg2[43 * steps + ((cycle - 0) & mask)];
    assert(x977 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x978 = arg2[44 * steps + ((cycle - 0) & mask)];
    assert(x978 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x979 = x978 - x964;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x980 = x977 - x963;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x981 = x980 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x982 = x980 * x981;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x982 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x980 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x978 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x983 = x964 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x984 = x964 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x985 = x983 * x984;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x985 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x986 = x4 - x980;
    if (x986 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x987 = x979 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x988 = x979 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x989 = x979 * x987;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x990 = x989 * x988;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x990 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x991 = arg2[45 * steps + ((cycle - 0) & mask)];
    assert(x991 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x992 = arg2[46 * steps + ((cycle - 0) & mask)];
    assert(x992 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x993 = x992 - x978;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x994 = x991 - x977;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x995 = x994 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x996 = x994 * x995;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x996 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x994 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x992 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x997 = x978 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x998 = x978 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x999 = x997 * x998;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x999 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1000 = x4 - x994;
    if (x1000 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1001 = x993 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1002 = x993 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1003 = x993 * x1001;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1004 = x1003 * x1002;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1004 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1005 = arg2[47 * steps + ((cycle - 0) & mask)];
    assert(x1005 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1006 = arg2[48 * steps + ((cycle - 0) & mask)];
    assert(x1006 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1007 = x1006 - x992;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1008 = x1005 - x991;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1009 = x1008 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1010 = x1008 * x1009;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1010 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1008 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1006 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1011 = x992 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1012 = x992 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1013 = x1011 * x1012;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1013 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1014 = x4 - x1008;
    if (x1014 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1015 = x1007 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1016 = x1007 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1017 = x1007 * x1015;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1018 = x1017 * x1016;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1018 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1019 = arg2[49 * steps + ((cycle - 0) & mask)];
    assert(x1019 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1020 = arg2[50 * steps + ((cycle - 0) & mask)];
    assert(x1020 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1021 = x1020 - x1006;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1022 = x1019 - x1005;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1023 = x1022 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1024 = x1022 * x1023;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1024 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1022 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1020 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1025 = x1006 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1026 = x1006 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1027 = x1025 * x1026;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1027 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1028 = x4 - x1022;
    if (x1028 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1029 = x1021 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1030 = x1021 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1031 = x1021 * x1029;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1032 = x1031 * x1030;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1032 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1033 = arg2[51 * steps + ((cycle - 0) & mask)];
    assert(x1033 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1034 = arg2[52 * steps + ((cycle - 0) & mask)];
    assert(x1034 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1035 = x1034 - x1020;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1036 = x1033 - x1019;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1037 = x1036 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1038 = x1036 * x1037;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1038 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1036 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1034 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1039 = x1020 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1040 = x1020 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1041 = x1039 * x1040;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1041 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1042 = x4 - x1036;
    if (x1042 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1043 = x1035 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1044 = x1035 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1045 = x1035 * x1043;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1046 = x1045 * x1044;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1046 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1047 = arg2[53 * steps + ((cycle - 0) & mask)];
    assert(x1047 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1048 = arg2[54 * steps + ((cycle - 0) & mask)];
    assert(x1048 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1049 = x1048 - x1034;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1050 = x1047 - x1033;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1051 = x1050 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1052 = x1050 * x1051;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1052 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1050 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1048 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1053 = x1034 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1054 = x1034 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1055 = x1053 * x1054;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1055 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1056 = x4 - x1050;
    if (x1056 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1057 = x1049 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1058 = x1049 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1059 = x1049 * x1057;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1060 = x1059 * x1058;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1060 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1061 = arg2[55 * steps + ((cycle - 0) & mask)];
    assert(x1061 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1062 = arg2[56 * steps + ((cycle - 0) & mask)];
    assert(x1062 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1063 = x1062 - x1048;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1064 = x1061 - x1047;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1065 = x1064 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1066 = x1064 * x1065;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1066 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1064 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1062 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1067 = x1048 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1068 = x1048 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1069 = x1067 * x1068;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1069 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1070 = x4 - x1064;
    if (x1070 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1071 = x1063 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1072 = x1063 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1073 = x1063 * x1071;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1074 = x1073 * x1072;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1074 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1075 = arg2[57 * steps + ((cycle - 0) & mask)];
    assert(x1075 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1076 = arg2[58 * steps + ((cycle - 0) & mask)];
    assert(x1076 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1077 = x1076 - x1062;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1078 = x1075 - x1061;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1079 = x1078 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1080 = x1078 * x1079;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1080 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1078 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1076 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1081 = x1062 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1082 = x1062 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1083 = x1081 * x1082;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1083 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1084 = x4 - x1078;
    if (x1084 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1085 = x1077 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1086 = x1077 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1087 = x1077 * x1085;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1088 = x1087 * x1086;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1088 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1089 = arg2[59 * steps + ((cycle - 0) & mask)];
    assert(x1089 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1090 = arg2[60 * steps + ((cycle - 0) & mask)];
    assert(x1090 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1091 = x1090 - x1076;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1092 = x1089 - x1075;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1093 = x1092 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1094 = x1092 * x1093;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1094 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1092 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1090 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1095 = x1076 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1096 = x1076 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1097 = x1095 * x1096;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1097 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1098 = x4 - x1092;
    if (x1098 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1099 = x1091 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1100 = x1091 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1101 = x1091 * x1099;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1102 = x1101 * x1100;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1102 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1103 = arg2[61 * steps + ((cycle - 0) & mask)];
    assert(x1103 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1104 = arg2[62 * steps + ((cycle - 0) & mask)];
    assert(x1104 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1105 = x1104 - x1090;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1106 = x1103 - x1089;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1107 = x1106 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1108 = x1106 * x1107;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1108 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1106 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1104 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1109 = x1090 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1110 = x1090 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1111 = x1109 * x1110;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1111 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1112 = x4 - x1106;
    if (x1112 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1113 = x1105 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1114 = x1105 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1115 = x1105 * x1113;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1116 = x1115 * x1114;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1116 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1117 = arg2[63 * steps + ((cycle - 0) & mask)];
    assert(x1117 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1118 = arg2[64 * steps + ((cycle - 0) & mask)];
    assert(x1118 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1119 = x1118 - x1104;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1120 = x1117 - x1103;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1121 = x1120 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1122 = x1120 * x1121;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1122 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1120 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1118 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1123 = x1104 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1124 = x1104 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1125 = x1123 * x1124;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1125 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1126 = x4 - x1120;
    if (x1126 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1127 = x1119 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1128 = x1119 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1129 = x1119 * x1127;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1130 = x1129 * x1128;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1130 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1131 = arg2[65 * steps + ((cycle - 0) & mask)];
    assert(x1131 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1132 = arg2[66 * steps + ((cycle - 0) & mask)];
    assert(x1132 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1133 = x1132 - x1118;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1134 = x1131 - x1117;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1135 = x1134 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1136 = x1134 * x1135;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1136 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1134 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1132 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1137 = x1118 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1138 = x1118 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1139 = x1137 * x1138;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1139 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1140 = x4 - x1134;
    if (x1140 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1141 = x1133 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1142 = x1133 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1143 = x1133 * x1141;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1144 = x1143 * x1142;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1144 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1145 = arg2[67 * steps + ((cycle - 0) & mask)];
    assert(x1145 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1146 = arg2[68 * steps + ((cycle - 0) & mask)];
    assert(x1146 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1147 = x1146 - x1132;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1148 = x1145 - x1131;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1149 = x1148 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1150 = x1148 * x1149;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1150 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1148 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1146 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1151 = x1132 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1152 = x1132 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1153 = x1151 * x1152;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1153 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1154 = x4 - x1148;
    if (x1154 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1155 = x1147 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1156 = x1147 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1157 = x1147 * x1155;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1158 = x1157 * x1156;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1158 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1159 = arg2[0 * steps + ((cycle - 0) & mask)];
    assert(x1159 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1160 = arg2[1 * steps + ((cycle - 0) & mask)];
    assert(x1160 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1161 = x1160 - x1146;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1162 = x1159 - x1145;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1163 = x1162 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1164 = x1162 * x1163;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1164 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1162 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1160 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1165 = x1146 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1166 = x1146 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1167 = x1165 * x1166;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1167 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1168 = x4 - x1162;
    if (x1168 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1169 = x1161 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1170 = x1161 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1171 = x1161 * x1169;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1172 = x1171 * x1170;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1172 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
  }
  if (x8 != 0) {
    {
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1173 = extern_outs[0];
      auto x1174 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[37 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1173);
        reg = x1173;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[38 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1174);
        reg = x1174;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1175 = extern_outs[0];
      auto x1176 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[39 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1175);
        reg = x1175;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[40 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1176);
        reg = x1176;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1177 = extern_outs[0];
      auto x1178 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[41 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1177);
        reg = x1177;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[42 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1178);
        reg = x1178;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1179 = extern_outs[0];
      auto x1180 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[43 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1179);
        reg = x1179;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[44 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1180);
        reg = x1180;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1181 = extern_outs[0];
      auto x1182 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[45 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1181);
        reg = x1181;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[46 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1182);
        reg = x1182;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1183 = extern_outs[0];
      auto x1184 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[47 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1183);
        reg = x1183;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[48 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1184);
        reg = x1184;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1185 = extern_outs[0];
      auto x1186 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[49 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1185);
        reg = x1185;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1186);
        reg = x1186;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1187 = extern_outs[0];
      auto x1188 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1187);
        reg = x1187;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1188);
        reg = x1188;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1189 = extern_outs[0];
      auto x1190 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1189);
        reg = x1189;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1190);
        reg = x1190;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1191 = extern_outs[0];
      auto x1192 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1191);
        reg = x1191;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1192);
        reg = x1192;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1193 = extern_outs[0];
      auto x1194 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1193);
        reg = x1193;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1194);
        reg = x1194;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1195 = extern_outs[0];
      auto x1196 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1195);
        reg = x1195;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1196);
        reg = x1196;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1197 = extern_outs[0];
      auto x1198 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1197);
        reg = x1197;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1198);
        reg = x1198;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1199 = extern_outs[0];
      auto x1200 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1199);
        reg = x1199;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1200);
        reg = x1200;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1201 = extern_outs[0];
      auto x1202 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1201);
        reg = x1201;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1202);
        reg = x1202;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1203 = extern_outs[0];
      auto x1204 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1203);
        reg = x1203;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1204);
        reg = x1204;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1205 = extern_outs[0];
      auto x1206 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1205);
        reg = x1205;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1206);
        reg = x1206;
      }
    }
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1207 = arg2[37 * steps + ((cycle - 0) & mask)];
    assert(x1207 != Fp::invalid());
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1208 = arg2[38 * steps + ((cycle - 0) & mask)];
    assert(x1208 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("zirgen/components/bytes.cpp":62:42))
    auto x1209 = arg2[0 * steps + ((cycle - 1) & mask)];
    assert(x1209 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("zirgen/components/bytes.cpp":63:40))
    auto x1210 = arg2[1 * steps + ((cycle - 1) & mask)];
    assert(x1210 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1211 = x1208 - x1210;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1212 = x1207 - x1209;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1213 = x1212 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1214 = x1212 * x1213;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1214 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1212 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1208 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1215 = x1210 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1216 = x1210 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1217 = x1215 * x1216;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1217 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1218 = x4 - x1212;
    if (x1218 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1219 = x1211 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1220 = x1211 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1221 = x1211 * x1219;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1222 = x1221 * x1220;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1222 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1223 = arg2[39 * steps + ((cycle - 0) & mask)];
    assert(x1223 != Fp::invalid());
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1224 = arg2[40 * steps + ((cycle - 0) & mask)];
    assert(x1224 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1225 = x1224 - x1208;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1226 = x1223 - x1207;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1227 = x1226 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1228 = x1226 * x1227;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1228 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1226 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1224 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1229 = x1208 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1230 = x1208 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1231 = x1229 * x1230;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1231 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1232 = x4 - x1226;
    if (x1232 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1233 = x1225 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1234 = x1225 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1235 = x1225 * x1233;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1236 = x1235 * x1234;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1236 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1237 = arg2[41 * steps + ((cycle - 0) & mask)];
    assert(x1237 != Fp::invalid());
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1238 = arg2[42 * steps + ((cycle - 0) & mask)];
    assert(x1238 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1239 = x1238 - x1224;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1240 = x1237 - x1223;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1241 = x1240 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1242 = x1240 * x1241;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1242 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1240 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1238 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1243 = x1224 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1244 = x1224 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1245 = x1243 * x1244;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1245 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1246 = x4 - x1240;
    if (x1246 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1247 = x1239 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1248 = x1239 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1249 = x1239 * x1247;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1250 = x1249 * x1248;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1250 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1251 = arg2[43 * steps + ((cycle - 0) & mask)];
    assert(x1251 != Fp::invalid());
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1252 = arg2[44 * steps + ((cycle - 0) & mask)];
    assert(x1252 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1253 = x1252 - x1238;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1254 = x1251 - x1237;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1255 = x1254 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1256 = x1254 * x1255;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1256 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1254 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1252 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1257 = x1238 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1258 = x1238 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1259 = x1257 * x1258;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1259 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1260 = x4 - x1254;
    if (x1260 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1261 = x1253 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1262 = x1253 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1263 = x1253 * x1261;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1264 = x1263 * x1262;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1264 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1265 = arg2[45 * steps + ((cycle - 0) & mask)];
    assert(x1265 != Fp::invalid());
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1266 = arg2[46 * steps + ((cycle - 0) & mask)];
    assert(x1266 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1267 = x1266 - x1252;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1268 = x1265 - x1251;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1269 = x1268 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1270 = x1268 * x1269;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1270 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1268 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1266 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1271 = x1252 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1272 = x1252 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1273 = x1271 * x1272;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1273 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1274 = x4 - x1268;
    if (x1274 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1275 = x1267 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1276 = x1267 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1277 = x1267 * x1275;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1278 = x1277 * x1276;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1278 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1279 = arg2[47 * steps + ((cycle - 0) & mask)];
    assert(x1279 != Fp::invalid());
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1280 = arg2[48 * steps + ((cycle - 0) & mask)];
    assert(x1280 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1281 = x1280 - x1266;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1282 = x1279 - x1265;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1283 = x1282 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1284 = x1282 * x1283;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1284 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1282 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1280 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1285 = x1266 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1286 = x1266 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1287 = x1285 * x1286;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1287 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1288 = x4 - x1282;
    if (x1288 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1289 = x1281 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1290 = x1281 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1291 = x1281 * x1289;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1292 = x1291 * x1290;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1292 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1293 = arg2[49 * steps + ((cycle - 0) & mask)];
    assert(x1293 != Fp::invalid());
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1294 = arg2[50 * steps + ((cycle - 0) & mask)];
    assert(x1294 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1295 = x1294 - x1280;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1296 = x1293 - x1279;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1297 = x1296 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1298 = x1296 * x1297;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1298 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1296 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1294 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1299 = x1280 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1300 = x1280 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1301 = x1299 * x1300;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1301 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1302 = x4 - x1296;
    if (x1302 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1303 = x1295 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1304 = x1295 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1305 = x1295 * x1303;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1306 = x1305 * x1304;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1306 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1307 = arg2[51 * steps + ((cycle - 0) & mask)];
    assert(x1307 != Fp::invalid());
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1308 = arg2[52 * steps + ((cycle - 0) & mask)];
    assert(x1308 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1309 = x1308 - x1294;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1310 = x1307 - x1293;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1311 = x1310 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1312 = x1310 * x1311;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1312 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1310 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1308 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1313 = x1294 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1314 = x1294 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1315 = x1313 * x1314;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1315 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1316 = x4 - x1310;
    if (x1316 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1317 = x1309 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1318 = x1309 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1319 = x1309 * x1317;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1320 = x1319 * x1318;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1320 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1321 = arg2[53 * steps + ((cycle - 0) & mask)];
    assert(x1321 != Fp::invalid());
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1322 = arg2[54 * steps + ((cycle - 0) & mask)];
    assert(x1322 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1323 = x1322 - x1308;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1324 = x1321 - x1307;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1325 = x1324 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1326 = x1324 * x1325;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1326 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1324 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1322 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1327 = x1308 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1328 = x1308 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1329 = x1327 * x1328;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1329 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1330 = x4 - x1324;
    if (x1330 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1331 = x1323 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1332 = x1323 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1333 = x1323 * x1331;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1334 = x1333 * x1332;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1334 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1335 = arg2[55 * steps + ((cycle - 0) & mask)];
    assert(x1335 != Fp::invalid());
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1336 = arg2[56 * steps + ((cycle - 0) & mask)];
    assert(x1336 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1337 = x1336 - x1322;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1338 = x1335 - x1321;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1339 = x1338 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1340 = x1338 * x1339;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1340 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1338 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1336 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1341 = x1322 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1342 = x1322 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1343 = x1341 * x1342;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1343 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1344 = x4 - x1338;
    if (x1344 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1345 = x1337 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1346 = x1337 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1347 = x1337 * x1345;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1348 = x1347 * x1346;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1348 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1349 = arg2[57 * steps + ((cycle - 0) & mask)];
    assert(x1349 != Fp::invalid());
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1350 = arg2[58 * steps + ((cycle - 0) & mask)];
    assert(x1350 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1351 = x1350 - x1336;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1352 = x1349 - x1335;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1353 = x1352 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1354 = x1352 * x1353;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1354 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1352 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1350 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1355 = x1336 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1356 = x1336 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1357 = x1355 * x1356;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1357 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1358 = x4 - x1352;
    if (x1358 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1359 = x1351 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1360 = x1351 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1361 = x1351 * x1359;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1362 = x1361 * x1360;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1362 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1363 = arg2[59 * steps + ((cycle - 0) & mask)];
    assert(x1363 != Fp::invalid());
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1364 = arg2[60 * steps + ((cycle - 0) & mask)];
    assert(x1364 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1365 = x1364 - x1350;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1366 = x1363 - x1349;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1367 = x1366 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1368 = x1366 * x1367;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1368 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1366 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1364 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1369 = x1350 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1370 = x1350 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1371 = x1369 * x1370;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1371 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1372 = x4 - x1366;
    if (x1372 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1373 = x1365 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1374 = x1365 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1375 = x1365 * x1373;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1376 = x1375 * x1374;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1376 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1377 = arg2[61 * steps + ((cycle - 0) & mask)];
    assert(x1377 != Fp::invalid());
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1378 = arg2[62 * steps + ((cycle - 0) & mask)];
    assert(x1378 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1379 = x1378 - x1364;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1380 = x1377 - x1363;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1381 = x1380 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1382 = x1380 * x1381;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1382 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1380 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1378 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1383 = x1364 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1384 = x1364 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1385 = x1383 * x1384;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1385 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1386 = x4 - x1380;
    if (x1386 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1387 = x1379 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1388 = x1379 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1389 = x1379 * x1387;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1390 = x1389 * x1388;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1390 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1391 = arg2[63 * steps + ((cycle - 0) & mask)];
    assert(x1391 != Fp::invalid());
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1392 = arg2[64 * steps + ((cycle - 0) & mask)];
    assert(x1392 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1393 = x1392 - x1378;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1394 = x1391 - x1377;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1395 = x1394 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1396 = x1394 * x1395;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1396 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1394 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1392 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1397 = x1378 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1398 = x1378 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1399 = x1397 * x1398;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1399 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1400 = x4 - x1394;
    if (x1400 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1401 = x1393 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1402 = x1393 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1403 = x1393 * x1401;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1404 = x1403 * x1402;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1404 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1405 = arg2[65 * steps + ((cycle - 0) & mask)];
    assert(x1405 != Fp::invalid());
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1406 = arg2[66 * steps + ((cycle - 0) & mask)];
    assert(x1406 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1407 = x1406 - x1392;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1408 = x1405 - x1391;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1409 = x1408 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1410 = x1408 * x1409;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1410 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1408 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1406 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1411 = x1392 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1412 = x1392 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1413 = x1411 * x1412;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1413 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1414 = x4 - x1408;
    if (x1414 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1415 = x1407 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1416 = x1407 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1417 = x1407 * x1415;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1418 = x1417 * x1416;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1418 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1419 = arg2[67 * steps + ((cycle - 0) & mask)];
    assert(x1419 != Fp::invalid());
    // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1420 = arg2[68 * steps + ((cycle - 0) & mask)];
    assert(x1420 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1421 = x1420 - x1406;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1422 = x1419 - x1405;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1423 = x1422 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1424 = x1422 * x1423;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1424 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1422 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1420 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1425 = x1406 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1426 = x1406 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1427 = x1425 * x1426;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1427 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1428 = x4 - x1422;
    if (x1428 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1429 = x1421 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1430 = x1421 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1431 = x1421 * x1429;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1432 = x1431 * x1430;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1432 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1433 = arg2[0 * steps + ((cycle - 0) & mask)];
    assert(x1433 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1434 = arg2[1 * steps + ((cycle - 0) & mask)];
    assert(x1434 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1435 = x1434 - x1420;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1436 = x1433 - x1419;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1437 = x1436 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1438 = x1436 * x1437;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1438 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1436 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1434 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1439 = x1420 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1440 = x1420 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1441 = x1439 * x1440;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1441 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1442 = x4 - x1436;
    if (x1442 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1443 = x1435 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1444 = x1435 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1445 = x1435 * x1443;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1446 = x1445 * x1444;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1446 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
  }
  if (x9 != 0) {
    {
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1447 = extern_outs[0];
      auto x1448 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[37 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1447);
        reg = x1447;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[38 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1448);
        reg = x1448;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1449 = extern_outs[0];
      auto x1450 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[39 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1449);
        reg = x1449;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[40 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1450);
        reg = x1450;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1451 = extern_outs[0];
      auto x1452 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[41 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1451);
        reg = x1451;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[42 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1452);
        reg = x1452;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1453 = extern_outs[0];
      auto x1454 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[43 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1453);
        reg = x1453;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[44 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1454);
        reg = x1454;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1455 = extern_outs[0];
      auto x1456 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[45 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1455);
        reg = x1455;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[46 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1456);
        reg = x1456;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1457 = extern_outs[0];
      auto x1458 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[47 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1457);
        reg = x1457;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[48 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1458);
        reg = x1458;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1459 = extern_outs[0];
      auto x1460 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[49 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1459);
        reg = x1459;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1460);
        reg = x1460;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1461 = extern_outs[0];
      auto x1462 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1461);
        reg = x1461;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1462);
        reg = x1462;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1463 = extern_outs[0];
      auto x1464 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1463);
        reg = x1463;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1464);
        reg = x1464;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1465 = extern_outs[0];
      auto x1466 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1465);
        reg = x1465;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1466);
        reg = x1466;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1467 = extern_outs[0];
      auto x1468 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1467);
        reg = x1467;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1468);
        reg = x1468;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1469 = extern_outs[0];
      auto x1470 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1469);
        reg = x1469;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1470);
        reg = x1470;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1471 = extern_outs[0];
      auto x1472 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1471);
        reg = x1471;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1472);
        reg = x1472;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1473 = extern_outs[0];
      auto x1474 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1473);
        reg = x1473;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1474);
        reg = x1474;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1475 = extern_outs[0];
      auto x1476 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1475);
        reg = x1475;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1476);
        reg = x1476;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1477 = extern_outs[0];
      auto x1478 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1477);
        reg = x1477;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1478);
        reg = x1478;
      }
      extern_plonkRead_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      auto x1479 = extern_outs[0];
      auto x1480 = extern_outs[1];
      // loc("zirgen/components/bytes.cpp":16:3)
      {
        auto& reg = arg2[0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1479);
        reg = x1479;
      }
      // loc("zirgen/components/bytes.cpp":17:3)
      {
        auto& reg = arg2[1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1480);
        reg = x1480;
      }
    }
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1481 = arg2[37 * steps + ((cycle - 0) & mask)];
    assert(x1481 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1482 = arg2[38 * steps + ((cycle - 0) & mask)];
    assert(x1482 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("zirgen/components/bytes.cpp":62:42))
    auto x1483 = arg2[0 * steps + ((cycle - 1) & mask)];
    assert(x1483 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("zirgen/components/bytes.cpp":63:40))
    auto x1484 = arg2[1 * steps + ((cycle - 1) & mask)];
    assert(x1484 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1485 = x1482 - x1484;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1486 = x1481 - x1483;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1487 = x1486 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1488 = x1486 * x1487;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1488 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1486 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1482 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1489 = x1484 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1490 = x1484 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1491 = x1489 * x1490;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1491 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1492 = x4 - x1486;
    if (x1492 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1493 = x1485 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1494 = x1485 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1495 = x1485 * x1493;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1496 = x1495 * x1494;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1496 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1497 = arg2[39 * steps + ((cycle - 0) & mask)];
    assert(x1497 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1498 = arg2[40 * steps + ((cycle - 0) & mask)];
    assert(x1498 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1499 = x1498 - x1482;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1500 = x1497 - x1481;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1501 = x1500 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1502 = x1500 * x1501;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1502 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1500 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1498 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1503 = x1482 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1504 = x1482 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1505 = x1503 * x1504;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1505 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1506 = x4 - x1500;
    if (x1506 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1507 = x1499 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1508 = x1499 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1509 = x1499 * x1507;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1510 = x1509 * x1508;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1510 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1511 = arg2[41 * steps + ((cycle - 0) & mask)];
    assert(x1511 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1512 = arg2[42 * steps + ((cycle - 0) & mask)];
    assert(x1512 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1513 = x1512 - x1498;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1514 = x1511 - x1497;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1515 = x1514 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1516 = x1514 * x1515;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1516 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1514 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1512 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1517 = x1498 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1518 = x1498 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1519 = x1517 * x1518;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1519 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1520 = x4 - x1514;
    if (x1520 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1521 = x1513 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1522 = x1513 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1523 = x1513 * x1521;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1524 = x1523 * x1522;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1524 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1525 = arg2[43 * steps + ((cycle - 0) & mask)];
    assert(x1525 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1526 = arg2[44 * steps + ((cycle - 0) & mask)];
    assert(x1526 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1527 = x1526 - x1512;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1528 = x1525 - x1511;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1529 = x1528 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1530 = x1528 * x1529;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1530 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1528 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1526 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1531 = x1512 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1532 = x1512 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1533 = x1531 * x1532;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1533 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1534 = x4 - x1528;
    if (x1534 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1535 = x1527 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1536 = x1527 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1537 = x1527 * x1535;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1538 = x1537 * x1536;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1538 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1539 = arg2[45 * steps + ((cycle - 0) & mask)];
    assert(x1539 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1540 = arg2[46 * steps + ((cycle - 0) & mask)];
    assert(x1540 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1541 = x1540 - x1526;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1542 = x1539 - x1525;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1543 = x1542 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1544 = x1542 * x1543;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1544 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1542 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1540 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1545 = x1526 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1546 = x1526 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1547 = x1545 * x1546;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1547 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1548 = x4 - x1542;
    if (x1548 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1549 = x1541 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1550 = x1541 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1551 = x1541 * x1549;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1552 = x1551 * x1550;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1552 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1553 = arg2[47 * steps + ((cycle - 0) & mask)];
    assert(x1553 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1554 = arg2[48 * steps + ((cycle - 0) & mask)];
    assert(x1554 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1555 = x1554 - x1540;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1556 = x1553 - x1539;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1557 = x1556 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1558 = x1556 * x1557;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1558 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1556 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1554 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1559 = x1540 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1560 = x1540 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1561 = x1559 * x1560;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1561 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1562 = x4 - x1556;
    if (x1562 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1563 = x1555 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1564 = x1555 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1565 = x1555 * x1563;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1566 = x1565 * x1564;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1566 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1567 = arg2[49 * steps + ((cycle - 0) & mask)];
    assert(x1567 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1568 = arg2[50 * steps + ((cycle - 0) & mask)];
    assert(x1568 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1569 = x1568 - x1554;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1570 = x1567 - x1553;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1571 = x1570 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1572 = x1570 * x1571;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1572 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1570 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1568 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1573 = x1554 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1574 = x1554 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1575 = x1573 * x1574;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1575 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1576 = x4 - x1570;
    if (x1576 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1577 = x1569 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1578 = x1569 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1579 = x1569 * x1577;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1580 = x1579 * x1578;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1580 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1581 = arg2[51 * steps + ((cycle - 0) & mask)];
    assert(x1581 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1582 = arg2[52 * steps + ((cycle - 0) & mask)];
    assert(x1582 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1583 = x1582 - x1568;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1584 = x1581 - x1567;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1585 = x1584 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1586 = x1584 * x1585;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1586 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1584 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1582 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1587 = x1568 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1588 = x1568 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1589 = x1587 * x1588;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1589 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1590 = x4 - x1584;
    if (x1590 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1591 = x1583 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1592 = x1583 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1593 = x1583 * x1591;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1594 = x1593 * x1592;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1594 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1595 = arg2[53 * steps + ((cycle - 0) & mask)];
    assert(x1595 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1596 = arg2[54 * steps + ((cycle - 0) & mask)];
    assert(x1596 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1597 = x1596 - x1582;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1598 = x1595 - x1581;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1599 = x1598 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1600 = x1598 * x1599;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1600 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1598 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1596 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1601 = x1582 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1602 = x1582 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1603 = x1601 * x1602;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1603 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1604 = x4 - x1598;
    if (x1604 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1605 = x1597 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1606 = x1597 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1607 = x1597 * x1605;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1608 = x1607 * x1606;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1608 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1609 = arg2[55 * steps + ((cycle - 0) & mask)];
    assert(x1609 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1610 = arg2[56 * steps + ((cycle - 0) & mask)];
    assert(x1610 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1611 = x1610 - x1596;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1612 = x1609 - x1595;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1613 = x1612 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1614 = x1612 * x1613;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1614 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1612 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1610 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1615 = x1596 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1616 = x1596 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1617 = x1615 * x1616;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1617 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1618 = x4 - x1612;
    if (x1618 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1619 = x1611 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1620 = x1611 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1621 = x1611 * x1619;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1622 = x1621 * x1620;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1622 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1623 = arg2[57 * steps + ((cycle - 0) & mask)];
    assert(x1623 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1624 = arg2[58 * steps + ((cycle - 0) & mask)];
    assert(x1624 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1625 = x1624 - x1610;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1626 = x1623 - x1609;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1627 = x1626 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1628 = x1626 * x1627;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1628 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1626 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1624 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1629 = x1610 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1630 = x1610 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1631 = x1629 * x1630;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1631 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1632 = x4 - x1626;
    if (x1632 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1633 = x1625 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1634 = x1625 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1635 = x1625 * x1633;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1636 = x1635 * x1634;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1636 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1637 = arg2[59 * steps + ((cycle - 0) & mask)];
    assert(x1637 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1638 = arg2[60 * steps + ((cycle - 0) & mask)];
    assert(x1638 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1639 = x1638 - x1624;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1640 = x1637 - x1623;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1641 = x1640 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1642 = x1640 * x1641;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1642 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1640 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1638 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1643 = x1624 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1644 = x1624 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1645 = x1643 * x1644;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1645 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1646 = x4 - x1640;
    if (x1646 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1647 = x1639 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1648 = x1639 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1649 = x1639 * x1647;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1650 = x1649 * x1648;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1650 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1651 = arg2[61 * steps + ((cycle - 0) & mask)];
    assert(x1651 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1652 = arg2[62 * steps + ((cycle - 0) & mask)];
    assert(x1652 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1653 = x1652 - x1638;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1654 = x1651 - x1637;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1655 = x1654 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1656 = x1654 * x1655;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1656 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1654 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1652 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1657 = x1638 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1658 = x1638 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1659 = x1657 * x1658;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1659 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1660 = x4 - x1654;
    if (x1660 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1661 = x1653 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1662 = x1653 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1663 = x1653 * x1661;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1664 = x1663 * x1662;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1664 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1665 = arg2[63 * steps + ((cycle - 0) & mask)];
    assert(x1665 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1666 = arg2[64 * steps + ((cycle - 0) & mask)];
    assert(x1666 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1667 = x1666 - x1652;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1668 = x1665 - x1651;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1669 = x1668 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1670 = x1668 * x1669;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1670 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1668 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1666 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1671 = x1652 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1672 = x1652 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1673 = x1671 * x1672;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1673 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1674 = x4 - x1668;
    if (x1674 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1675 = x1667 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1676 = x1667 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1677 = x1667 * x1675;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1678 = x1677 * x1676;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1678 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1679 = arg2[65 * steps + ((cycle - 0) & mask)];
    assert(x1679 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1680 = arg2[66 * steps + ((cycle - 0) & mask)];
    assert(x1680 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1681 = x1680 - x1666;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1682 = x1679 - x1665;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1683 = x1682 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1684 = x1682 * x1683;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1684 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1682 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1680 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1685 = x1666 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1686 = x1666 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1687 = x1685 * x1686;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1687 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1688 = x4 - x1682;
    if (x1688 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1689 = x1681 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1690 = x1681 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1691 = x1681 * x1689;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1692 = x1691 * x1690;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1692 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1693 = arg2[67 * steps + ((cycle - 0) & mask)];
    assert(x1693 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1694 = arg2[68 * steps + ((cycle - 0) & mask)];
    assert(x1694 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1695 = x1694 - x1680;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1696 = x1693 - x1679;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1697 = x1696 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1698 = x1696 * x1697;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1698 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1696 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1694 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1699 = x1680 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1700 = x1680 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1701 = x1699 * x1700;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1701 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1702 = x4 - x1696;
    if (x1702 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1703 = x1695 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1704 = x1695 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1705 = x1695 * x1703;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1706 = x1705 * x1704;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1706 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1707 = arg2[0 * steps + ((cycle - 0) & mask)];
    assert(x1707 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1708 = arg2[1 * steps + ((cycle - 0) & mask)];
    assert(x1708 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1709 = x1708 - x1694;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1710 = x1707 - x1693;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1711 = x1710 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1712 = x1710 * x1711;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1712 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1710 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1708 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1713 = x1694 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1714 = x1694 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1715 = x1713 * x1714;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1715 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1716 = x4 - x1710;
    if (x1716 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1717 = x1709 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1718 = x1709 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1719 = x1709 * x1717;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1720 = x1719 * x1718;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1720 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
  }
  if (x10 != 0) {
    // loc("zirgen/components/bytes.cpp":26:3)
    {
      auto& reg = arg2[3 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x0);
      reg = x0;
    }
    // loc("zirgen/components/bytes.cpp":27:3)
    {
      auto& reg = arg2[4 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x0);
      reg = x0;
    }
    // loc("Top/mux(Mux)/bytes_fini(BytesFiniStep)/PlonkFini/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1721 = arg2[3 * steps + ((cycle - 0) & mask)];
    assert(x1721 != Fp::invalid());
    // loc("Top/mux(Mux)/bytes_fini(BytesFiniStep)/PlonkFini/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":154:27))
    auto x1722 = arg2[4 * steps + ((cycle - 0) & mask)];
    assert(x1722 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("zirgen/components/bytes.cpp":62:42))
    auto x1723 = arg2[0 * steps + ((cycle - 1) & mask)];
    assert(x1723 != Fp::invalid());
    // loc("Top/BytesHeader/element(BytesPlonkElement)/Reg"("zirgen/components/bytes.cpp":63:40))
    auto x1724 = arg2[1 * steps + ((cycle - 1) & mask)];
    assert(x1724 != Fp::invalid());
    // loc("zirgen/components/bytes.cpp":67:17)
    auto x1725 = x1722 - x1724;
    // loc("zirgen/components/bytes.cpp":66:18)
    auto x1726 = x1721 - x1723;
    // loc("zirgen/components/bytes.cpp":69:19)
    auto x1727 = x1726 - x4;
    // loc("zirgen/components/bytes.cpp":69:7)
    auto x1728 = x1726 * x1727;
    // loc("zirgen/components/bytes.cpp":69:7)
    assert(x1728 == 0 && "eqz failed at: zirgen/components/bytes.cpp:69");
    if (x1726 != 0) {
      // loc("zirgen/components/bytes.cpp":73:9)
      assert(x1722 == 0 && "eqz failed at: zirgen/components/bytes.cpp:73");
      // loc("zirgen/components/bytes.cpp":75:10)
      auto x1729 = x1724 - x0;
      // loc("zirgen/components/bytes.cpp":75:27)
      auto x1730 = x1724 - x2;
      // loc("zirgen/components/bytes.cpp":75:9)
      auto x1731 = x1729 * x1730;
      // loc("zirgen/components/bytes.cpp":75:9)
      assert(x1731 == 0 && "eqz failed at: zirgen/components/bytes.cpp:75");
    }
    // loc("zirgen/components/bytes.cpp":77:18)
    auto x1732 = x4 - x1726;
    if (x1732 != 0) {
      // loc("zirgen/components/bytes.cpp":79:20)
      auto x1733 = x1725 - x4;
      // loc("zirgen/components/bytes.cpp":79:36)
      auto x1734 = x1725 - x1;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1735 = x1725 * x1733;
      // loc("zirgen/components/bytes.cpp":79:9)
      auto x1736 = x1735 * x1734;
      // loc("zirgen/components/bytes.cpp":79:9)
      assert(x1736 == 0 && "eqz failed at: zirgen/components/bytes.cpp:79");
    }
  }
}
