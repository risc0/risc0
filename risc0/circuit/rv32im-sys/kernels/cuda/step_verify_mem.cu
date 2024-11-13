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

__device__ void step_verify_mem(
    void* ctx, uint32_t steps, uint32_t cycle, Fp* arg0, Fp* arg1, Fp* arg2, Fp* arg3, Fp* arg4) {
  uint32_t mask = steps - 1;
  Fp extern_args[96];
  Fp extern_outs[32];
  // loc(unknown)
  Fp x0(33554431);
  // loc(unknown)
  Fp x1(67108863);
  // loc(unknown)
  Fp x2(3);
  // loc(unknown)
  Fp x3(2005401601);
  // loc(unknown)
  Fp x4(255);
  // loc(unknown)
  Fp x5(2);
  // loc(unknown)
  Fp x6(0);
  // loc(unknown)
  Fp x7(1);
  // loc("Top/Code/OneHot/hot[1](Reg)"("./zirgen/components/mux.h":59:25))
  auto x8 = arg0[2 * steps + ((cycle - 0) & mask)];
  assert(x8 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[3](Reg)"("./zirgen/components/mux.h":59:25))
  auto x9 = arg0[4 * steps + ((cycle - 0) & mask)];
  assert(x9 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[4](Reg)"("./zirgen/components/mux.h":59:25))
  auto x10 = arg0[5 * steps + ((cycle - 0) & mask)];
  assert(x10 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[5](Reg)"("./zirgen/components/mux.h":59:25))
  auto x11 = arg0[6 * steps + ((cycle - 0) & mask)];
  assert(x11 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[6](Reg)"("./zirgen/components/mux.h":59:25))
  auto x12 = arg0[7 * steps + ((cycle - 0) & mask)];
  assert(x12 != Fp::invalid());
  // loc("Top/Code/OneHot/hot[2](Reg)"("zirgen/circuit/rv32im/v1/edsl/top.cpp":94:27))
  auto x13 = arg0[3 * steps + ((cycle - 0) & mask)];
  assert(x13 != Fp::invalid());
  if (x13 != 0) {
    // loc("zirgen/components/ram.cpp":25:3)
    {
      auto& reg = arg2[89 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("zirgen/components/ram.cpp":26:3)
    {
      auto& reg = arg2[90 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("zirgen/components/ram.cpp":27:3)
    {
      auto& reg = arg2[91 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("zirgen/components/u32.cpp":38:5)
    {
      auto& reg = arg2[92 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("zirgen/components/u32.cpp":38:5)
    {
      auto& reg = arg2[93 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("zirgen/components/u32.cpp":38:5)
    {
      auto& reg = arg2[94 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("zirgen/components/u32.cpp":38:5)
    {
      auto& reg = arg2[95 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("./zirgen/components/bits.h":37:23)
    {
      auto& reg = arg2[96 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("./zirgen/components/bits.h":37:23)
    {
      auto& reg = arg2[97 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    {
      // loc("zirgen/components/bytes.cpp":106:12)
      {
        auto& reg = arg2[3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x6);
        reg = x6;
      }
    }
    {
      // loc("zirgen/components/bytes.cpp":106:12)
      {
        auto& reg = arg2[4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x6);
        reg = x6;
      }
    }
    {
      // loc("zirgen/components/bytes.cpp":106:12)
      {
        auto& reg = arg2[5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x6);
        reg = x6;
      }
    }
    // loc("./zirgen/components/bits.h":78:23)
    {
      auto& reg = arg2[69 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
  }
  if (x9 != 0) {
    {
      extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
      auto x14 = extern_outs[0];
      auto x15 = extern_outs[1];
      auto x16 = extern_outs[2];
      auto x17 = extern_outs[3];
      auto x18 = extern_outs[4];
      auto x19 = extern_outs[5];
      auto x20 = extern_outs[6];
      // loc("zirgen/components/ram.cpp":46:3)
      {
        auto& reg = arg2[143 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x14);
        reg = x14;
      }
      // loc("zirgen/components/ram.cpp":47:3)
      {
        auto& reg = arg2[144 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x15);
        reg = x15;
      }
      // loc("zirgen/components/ram.cpp":48:3)
      {
        auto& reg = arg2[145 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x16);
        reg = x16;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[146 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x17);
        reg = x17;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[147 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x18);
        reg = x18;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[148 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x19);
        reg = x19;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[149 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x20);
        reg = x20;
      }
      extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
      auto x21 = extern_outs[0];
      auto x22 = extern_outs[1];
      auto x23 = extern_outs[2];
      auto x24 = extern_outs[3];
      auto x25 = extern_outs[4];
      auto x26 = extern_outs[5];
      auto x27 = extern_outs[6];
      // loc("zirgen/components/ram.cpp":46:3)
      {
        auto& reg = arg2[150 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x21);
        reg = x21;
      }
      // loc("zirgen/components/ram.cpp":47:3)
      {
        auto& reg = arg2[151 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x22);
        reg = x22;
      }
      // loc("zirgen/components/ram.cpp":48:3)
      {
        auto& reg = arg2[152 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x23);
        reg = x23;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[153 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x24);
        reg = x24;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[154 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x25);
        reg = x25;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[155 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x26);
        reg = x26;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[156 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x27);
        reg = x27;
      }
      extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
      auto x28 = extern_outs[0];
      auto x29 = extern_outs[1];
      auto x30 = extern_outs[2];
      auto x31 = extern_outs[3];
      auto x32 = extern_outs[4];
      auto x33 = extern_outs[5];
      auto x34 = extern_outs[6];
      // loc("zirgen/components/ram.cpp":46:3)
      {
        auto& reg = arg2[157 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x28);
        reg = x28;
      }
      // loc("zirgen/components/ram.cpp":47:3)
      {
        auto& reg = arg2[158 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x29);
        reg = x29;
      }
      // loc("zirgen/components/ram.cpp":48:3)
      {
        auto& reg = arg2[159 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x30);
        reg = x30;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[160 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x31);
        reg = x31;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[161 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x32);
        reg = x32;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[162 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x33);
        reg = x33;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[163 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x34);
        reg = x34;
      }
      extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
      auto x35 = extern_outs[0];
      auto x36 = extern_outs[1];
      auto x37 = extern_outs[2];
      auto x38 = extern_outs[3];
      auto x39 = extern_outs[4];
      auto x40 = extern_outs[5];
      auto x41 = extern_outs[6];
      // loc("zirgen/components/ram.cpp":46:3)
      {
        auto& reg = arg2[89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x35);
        reg = x35;
      }
      // loc("zirgen/components/ram.cpp":47:3)
      {
        auto& reg = arg2[90 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x36);
        reg = x36;
      }
      // loc("zirgen/components/ram.cpp":48:3)
      {
        auto& reg = arg2[91 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x37);
        reg = x37;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[92 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x38);
        reg = x38;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[93 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x39);
        reg = x39;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[94 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x40);
        reg = x40;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[95 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x41);
        reg = x41;
      }
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/Global/sys_exit_code(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x42 = arg1[104];
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x43 = arg2[146 * steps + ((cycle - 0) & mask)];
    assert(x43 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x44 = arg2[147 * steps + ((cycle - 0) & mask)];
    assert(x44 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x45 = arg2[148 * steps + ((cycle - 0) & mask)];
    assert(x45 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x46 = arg2[149 * steps + ((cycle - 0) & mask)];
    assert(x46 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
    auto x47 = arg2[90 * steps + ((cycle - 1) & mask)];
    assert(x47 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x48 = arg2[92 * steps + ((cycle - 1) & mask)];
    assert(x48 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x49 = arg2[93 * steps + ((cycle - 1) & mask)];
    assert(x49 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x50 = arg2[94 * steps + ((cycle - 1) & mask)];
    assert(x50 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x51 = arg2[95 * steps + ((cycle - 1) & mask)];
    assert(x51 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("zirgen/components/ram.cpp":65:40))
    auto x52 = arg2[89 * steps + ((cycle - 1) & mask)];
    assert(x52 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("zirgen/components/ram.cpp":67:42))
    auto x53 = arg2[91 * steps + ((cycle - 1) & mask)];
    assert(x53 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x54 = arg2[97 * steps + ((cycle - 1) & mask)];
    assert(x54 != Fp::invalid());
    {
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x55 = arg2[143 * steps + ((cycle - 0) & mask)];
      assert(x55 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":85:35)
      auto x56 = x52 - x55;
      // loc("zirgen/components/ram.cpp":85:35)
      auto x57 = (x56 == 0) ? Fp(1) : Fp(0);
      // loc("zirgen/components/ram.cpp":85:27)
      auto x58 = x7 - x57;
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[164 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x58);
        reg = x58;
      }
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x59 = arg2[164 * steps + ((cycle - 0) & mask)];
    assert(x59 != Fp::invalid());
    if (x59 != 0) {
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x60 = arg2[145 * steps + ((cycle - 0) & mask)];
      assert(x60 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":97:9)
      auto x61 = x6 - x60;
      // loc("zirgen/components/ram.cpp":97:9)
      assert(x61 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x62 = arg2[143 * steps + ((cycle - 0) & mask)];
      assert(x62 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":99:17)
      auto x63 = x62 - x52;
      // loc("zirgen/components/ram.cpp":99:17)
      auto x64 = x63 - x7;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x65 = Fp(x64.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x65);
          reg = x65;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x66 = arg2[6 * steps + ((cycle - 0) & mask)];
      assert(x66 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x67 = x64 - x66;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x68 = x67 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x69 = Fp(x68.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x69);
          reg = x69;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x70 = arg2[7 * steps + ((cycle - 0) & mask)];
      assert(x70 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x71 = x68 - x70;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x72 = x71 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x73 = Fp(x72.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x73);
          reg = x73;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x74 = arg2[8 * steps + ((cycle - 0) & mask)];
      assert(x74 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x75 = x72 - x74;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x76 = x75 * x3;
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x76);
        reg = x76;
      }
      // loc("zirgen/components/ram.cpp":101:9)
      auto x77 = x42 * x54;
      // loc("zirgen/components/ram.cpp":101:9)
      assert(x77 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
    }
    // loc("zirgen/components/ram.cpp":105:19)
    auto x78 = x7 - x59;
    if (x78 != 0) {
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x79 = arg2[143 * steps + ((cycle - 0) & mask)];
      assert(x79 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":107:9)
      auto x80 = x52 - x79;
      // loc("zirgen/components/ram.cpp":107:9)
      assert(x80 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
      // loc("zirgen/components/ram.cpp":109:43)
      auto x81 = x47 * x2;
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x82 = arg2[144 * steps + ((cycle - 0) & mask)];
      assert(x82 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x83 = arg2[145 * steps + ((cycle - 0) & mask)];
      assert(x83 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":109:17)
      auto x84 = x82 * x2;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x85 = x84 + x83;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x86 = x85 - x81;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x87 = x86 + x53;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x88 = Fp(x87.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x88);
          reg = x88;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x89 = arg2[6 * steps + ((cycle - 0) & mask)];
      assert(x89 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x90 = x87 - x89;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x91 = x90 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x92 = Fp(x91.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x92);
          reg = x92;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x93 = arg2[7 * steps + ((cycle - 0) & mask)];
      assert(x93 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x94 = x91 - x93;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x95 = x94 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x96 = Fp(x95.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x96);
          reg = x96;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x97 = arg2[8 * steps + ((cycle - 0) & mask)];
      assert(x97 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x98 = x95 - x97;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x99 = x98 * x3;
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x99);
        reg = x99;
      }
      // loc("zirgen/components/ram.cpp":111:39)
      auto x100 = x5 - x83;
      if (x100 != 0) {
        // loc("zirgen/components/ram.cpp":111:43)
        auto x101 = x48 - x43;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x101 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x102 = x49 - x44;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x102 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x103 = x50 - x45;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x103 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x104 = x51 - x46;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x104 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
      }
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x105 = arg2[145 * steps + ((cycle - 0) & mask)];
    assert(x105 != Fp::invalid());
    // loc("zirgen/components/ram.cpp":115:17)
    auto x106 = x6 - x105;
    // loc("zirgen/components/ram.cpp":114:18)
    auto x107 = x7 - x105;
    // loc("zirgen/components/ram.cpp":115:54)
    auto x108 = x5 - x105;
    // loc("zirgen/components/ram.cpp":115:16)
    auto x109 = x106 * x108;
    // loc("zirgen/components/ram.cpp":114:17)
    auto x110 = x107 * x106;
    // loc("zirgen/components/ram.cpp":116:18)
    auto x111 = x107 * x108;
    if (x111 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[165 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x6);
        reg = x6;
      }
    }
    if (x110 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[165 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x7);
        reg = x7;
      }
    }
    if (x109 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[165 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x54);
        reg = x54;
      }
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
    auto x112 = arg2[144 * steps + ((cycle - 0) & mask)];
    assert(x112 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
    auto x113 = arg2[143 * steps + ((cycle - 0) & mask)];
    assert(x113 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x114 = arg2[153 * steps + ((cycle - 0) & mask)];
    assert(x114 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x115 = arg2[154 * steps + ((cycle - 0) & mask)];
    assert(x115 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x116 = arg2[155 * steps + ((cycle - 0) & mask)];
    assert(x116 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x117 = arg2[156 * steps + ((cycle - 0) & mask)];
    assert(x117 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x118 = arg2[165 * steps + ((cycle - 0) & mask)];
    assert(x118 != Fp::invalid());
    {
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x119 = arg2[150 * steps + ((cycle - 0) & mask)];
      assert(x119 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":85:35)
      auto x120 = x113 - x119;
      // loc("zirgen/components/ram.cpp":85:35)
      auto x121 = (x120 == 0) ? Fp(1) : Fp(0);
      // loc("zirgen/components/ram.cpp":85:27)
      auto x122 = x7 - x121;
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[166 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x122);
        reg = x122;
      }
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x123 = arg2[166 * steps + ((cycle - 0) & mask)];
    assert(x123 != Fp::invalid());
    if (x123 != 0) {
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x124 = arg2[152 * steps + ((cycle - 0) & mask)];
      assert(x124 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":97:9)
      auto x125 = x6 - x124;
      // loc("zirgen/components/ram.cpp":97:9)
      assert(x125 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x126 = arg2[150 * steps + ((cycle - 0) & mask)];
      assert(x126 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":99:17)
      auto x127 = x126 - x113;
      // loc("zirgen/components/ram.cpp":99:17)
      auto x128 = x127 - x7;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x129 = Fp(x128.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[9 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x129);
          reg = x129;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x130 = arg2[9 * steps + ((cycle - 0) & mask)];
      assert(x130 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x131 = x128 - x130;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x132 = x131 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x133 = Fp(x132.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[10 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x133);
          reg = x133;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x134 = arg2[10 * steps + ((cycle - 0) & mask)];
      assert(x134 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x135 = x132 - x134;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x136 = x135 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x137 = Fp(x136.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[11 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x137);
          reg = x137;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x138 = arg2[11 * steps + ((cycle - 0) & mask)];
      assert(x138 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x139 = x136 - x138;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x140 = x139 * x3;
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x140);
        reg = x140;
      }
      // loc("zirgen/components/ram.cpp":101:9)
      auto x141 = x42 * x118;
      // loc("zirgen/components/ram.cpp":101:9)
      assert(x141 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
    }
    // loc("zirgen/components/ram.cpp":105:19)
    auto x142 = x7 - x123;
    if (x142 != 0) {
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x143 = arg2[150 * steps + ((cycle - 0) & mask)];
      assert(x143 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":107:9)
      auto x144 = x113 - x143;
      // loc("zirgen/components/ram.cpp":107:9)
      assert(x144 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
      // loc("zirgen/components/ram.cpp":109:43)
      auto x145 = x112 * x2;
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x146 = arg2[151 * steps + ((cycle - 0) & mask)];
      assert(x146 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x147 = arg2[152 * steps + ((cycle - 0) & mask)];
      assert(x147 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":109:17)
      auto x148 = x146 * x2;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x149 = x148 + x147;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x150 = x149 - x145;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x151 = x150 + x105;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x152 = Fp(x151.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[9 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x152);
          reg = x152;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x153 = arg2[9 * steps + ((cycle - 0) & mask)];
      assert(x153 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x154 = x151 - x153;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x155 = x154 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x156 = Fp(x155.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[10 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x156);
          reg = x156;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x157 = arg2[10 * steps + ((cycle - 0) & mask)];
      assert(x157 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x158 = x155 - x157;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x159 = x158 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x160 = Fp(x159.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[11 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x160);
          reg = x160;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x161 = arg2[11 * steps + ((cycle - 0) & mask)];
      assert(x161 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x162 = x159 - x161;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x163 = x162 * x3;
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x163);
        reg = x163;
      }
      // loc("zirgen/components/ram.cpp":111:39)
      auto x164 = x5 - x147;
      if (x164 != 0) {
        // loc("zirgen/components/ram.cpp":111:43)
        auto x165 = x43 - x114;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x165 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x166 = x44 - x115;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x166 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x167 = x45 - x116;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x167 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x168 = x46 - x117;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x168 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
      }
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x169 = arg2[152 * steps + ((cycle - 0) & mask)];
    assert(x169 != Fp::invalid());
    // loc("zirgen/components/ram.cpp":115:17)
    auto x170 = x6 - x169;
    // loc("zirgen/components/ram.cpp":114:18)
    auto x171 = x7 - x169;
    // loc("zirgen/components/ram.cpp":115:54)
    auto x172 = x5 - x169;
    // loc("zirgen/components/ram.cpp":115:16)
    auto x173 = x170 * x172;
    // loc("zirgen/components/ram.cpp":114:17)
    auto x174 = x171 * x170;
    // loc("zirgen/components/ram.cpp":116:18)
    auto x175 = x171 * x172;
    if (x175 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[167 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x6);
        reg = x6;
      }
    }
    if (x174 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[167 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x7);
        reg = x7;
      }
    }
    if (x173 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[167 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x118);
        reg = x118;
      }
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
    auto x176 = arg2[151 * steps + ((cycle - 0) & mask)];
    assert(x176 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
    auto x177 = arg2[150 * steps + ((cycle - 0) & mask)];
    assert(x177 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x178 = arg2[160 * steps + ((cycle - 0) & mask)];
    assert(x178 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x179 = arg2[161 * steps + ((cycle - 0) & mask)];
    assert(x179 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x180 = arg2[162 * steps + ((cycle - 0) & mask)];
    assert(x180 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x181 = arg2[163 * steps + ((cycle - 0) & mask)];
    assert(x181 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x182 = arg2[167 * steps + ((cycle - 0) & mask)];
    assert(x182 != Fp::invalid());
    {
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x183 = arg2[157 * steps + ((cycle - 0) & mask)];
      assert(x183 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":85:35)
      auto x184 = x177 - x183;
      // loc("zirgen/components/ram.cpp":85:35)
      auto x185 = (x184 == 0) ? Fp(1) : Fp(0);
      // loc("zirgen/components/ram.cpp":85:27)
      auto x186 = x7 - x185;
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[168 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x186);
        reg = x186;
      }
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x187 = arg2[168 * steps + ((cycle - 0) & mask)];
    assert(x187 != Fp::invalid());
    if (x187 != 0) {
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x188 = arg2[159 * steps + ((cycle - 0) & mask)];
      assert(x188 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":97:9)
      auto x189 = x6 - x188;
      // loc("zirgen/components/ram.cpp":97:9)
      assert(x189 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x190 = arg2[157 * steps + ((cycle - 0) & mask)];
      assert(x190 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":99:17)
      auto x191 = x190 - x177;
      // loc("zirgen/components/ram.cpp":99:17)
      auto x192 = x191 - x7;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x193 = Fp(x192.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[12 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x193);
          reg = x193;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x194 = arg2[12 * steps + ((cycle - 0) & mask)];
      assert(x194 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x195 = x192 - x194;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x196 = x195 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x197 = Fp(x196.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[13 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x197);
          reg = x197;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x198 = arg2[13 * steps + ((cycle - 0) & mask)];
      assert(x198 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x199 = x196 - x198;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x200 = x199 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x201 = Fp(x200.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[14 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x201);
          reg = x201;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x202 = arg2[14 * steps + ((cycle - 0) & mask)];
      assert(x202 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x203 = x200 - x202;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x204 = x203 * x3;
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x204);
        reg = x204;
      }
      // loc("zirgen/components/ram.cpp":101:9)
      auto x205 = x42 * x182;
      // loc("zirgen/components/ram.cpp":101:9)
      assert(x205 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
    }
    // loc("zirgen/components/ram.cpp":105:19)
    auto x206 = x7 - x187;
    if (x206 != 0) {
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x207 = arg2[157 * steps + ((cycle - 0) & mask)];
      assert(x207 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":107:9)
      auto x208 = x177 - x207;
      // loc("zirgen/components/ram.cpp":107:9)
      assert(x208 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
      // loc("zirgen/components/ram.cpp":109:43)
      auto x209 = x176 * x2;
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x210 = arg2[158 * steps + ((cycle - 0) & mask)];
      assert(x210 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x211 = arg2[159 * steps + ((cycle - 0) & mask)];
      assert(x211 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":109:17)
      auto x212 = x210 * x2;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x213 = x212 + x211;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x214 = x213 - x209;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x215 = x214 + x169;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x216 = Fp(x215.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[12 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x216);
          reg = x216;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x217 = arg2[12 * steps + ((cycle - 0) & mask)];
      assert(x217 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x218 = x215 - x217;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x219 = x218 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x220 = Fp(x219.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[13 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x220);
          reg = x220;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x221 = arg2[13 * steps + ((cycle - 0) & mask)];
      assert(x221 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x222 = x219 - x221;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x223 = x222 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x224 = Fp(x223.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[14 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x224);
          reg = x224;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x225 = arg2[14 * steps + ((cycle - 0) & mask)];
      assert(x225 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x226 = x223 - x225;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x227 = x226 * x3;
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x227);
        reg = x227;
      }
      // loc("zirgen/components/ram.cpp":111:39)
      auto x228 = x5 - x211;
      if (x228 != 0) {
        // loc("zirgen/components/ram.cpp":111:43)
        auto x229 = x114 - x178;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x229 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x230 = x115 - x179;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x230 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x231 = x116 - x180;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x231 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x232 = x117 - x181;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x232 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
      }
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x233 = arg2[159 * steps + ((cycle - 0) & mask)];
    assert(x233 != Fp::invalid());
    // loc("zirgen/components/ram.cpp":115:17)
    auto x234 = x6 - x233;
    // loc("zirgen/components/ram.cpp":114:18)
    auto x235 = x7 - x233;
    // loc("zirgen/components/ram.cpp":115:54)
    auto x236 = x5 - x233;
    // loc("zirgen/components/ram.cpp":115:16)
    auto x237 = x234 * x236;
    // loc("zirgen/components/ram.cpp":114:17)
    auto x238 = x235 * x234;
    // loc("zirgen/components/ram.cpp":116:18)
    auto x239 = x235 * x236;
    if (x239 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[169 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x6);
        reg = x6;
      }
    }
    if (x238 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[169 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x7);
        reg = x7;
      }
    }
    if (x237 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[169 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x182);
        reg = x182;
      }
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
    auto x240 = arg2[158 * steps + ((cycle - 0) & mask)];
    assert(x240 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
    auto x241 = arg2[157 * steps + ((cycle - 0) & mask)];
    assert(x241 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x242 = arg2[92 * steps + ((cycle - 0) & mask)];
    assert(x242 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x243 = arg2[93 * steps + ((cycle - 0) & mask)];
    assert(x243 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x244 = arg2[94 * steps + ((cycle - 0) & mask)];
    assert(x244 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x245 = arg2[95 * steps + ((cycle - 0) & mask)];
    assert(x245 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x246 = arg2[169 * steps + ((cycle - 0) & mask)];
    assert(x246 != Fp::invalid());
    {
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x247 = arg2[89 * steps + ((cycle - 0) & mask)];
      assert(x247 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":85:35)
      auto x248 = x241 - x247;
      // loc("zirgen/components/ram.cpp":85:35)
      auto x249 = (x248 == 0) ? Fp(1) : Fp(0);
      // loc("zirgen/components/ram.cpp":85:27)
      auto x250 = x7 - x249;
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[96 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x250);
        reg = x250;
      }
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x251 = arg2[96 * steps + ((cycle - 0) & mask)];
    assert(x251 != Fp::invalid());
    if (x251 != 0) {
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x252 = arg2[91 * steps + ((cycle - 0) & mask)];
      assert(x252 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":97:9)
      auto x253 = x6 - x252;
      // loc("zirgen/components/ram.cpp":97:9)
      assert(x253 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x254 = arg2[89 * steps + ((cycle - 0) & mask)];
      assert(x254 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":99:17)
      auto x255 = x254 - x241;
      // loc("zirgen/components/ram.cpp":99:17)
      auto x256 = x255 - x7;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x257 = Fp(x256.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x257);
          reg = x257;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x258 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x258 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x259 = x256 - x258;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x260 = x259 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x261 = Fp(x260.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x261);
          reg = x261;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x262 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x262 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x263 = x260 - x262;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x264 = x263 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x265 = Fp(x264.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x265);
          reg = x265;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x266 = arg2[5 * steps + ((cycle - 0) & mask)];
      assert(x266 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x267 = x264 - x266;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x268 = x267 * x3;
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x268);
        reg = x268;
      }
      // loc("zirgen/components/ram.cpp":101:9)
      auto x269 = x42 * x246;
      // loc("zirgen/components/ram.cpp":101:9)
      assert(x269 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
    }
    // loc("zirgen/components/ram.cpp":105:19)
    auto x270 = x7 - x251;
    if (x270 != 0) {
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x271 = arg2[89 * steps + ((cycle - 0) & mask)];
      assert(x271 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":107:9)
      auto x272 = x241 - x271;
      // loc("zirgen/components/ram.cpp":107:9)
      assert(x272 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
      // loc("zirgen/components/ram.cpp":109:43)
      auto x273 = x240 * x2;
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x274 = arg2[90 * steps + ((cycle - 0) & mask)];
      assert(x274 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x275 = arg2[91 * steps + ((cycle - 0) & mask)];
      assert(x275 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":109:17)
      auto x276 = x274 * x2;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x277 = x276 + x275;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x278 = x277 - x273;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x279 = x278 + x233;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x280 = Fp(x279.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x280);
          reg = x280;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x281 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x281 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x282 = x279 - x281;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x283 = x282 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x284 = Fp(x283.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x284);
          reg = x284;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x285 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x285 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x286 = x283 - x285;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x287 = x286 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x288 = Fp(x287.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x288);
          reg = x288;
        }
      }
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x289 = arg2[5 * steps + ((cycle - 0) & mask)];
      assert(x289 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x290 = x287 - x289;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x291 = x290 * x3;
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x291);
        reg = x291;
      }
      // loc("zirgen/components/ram.cpp":111:39)
      auto x292 = x5 - x275;
      if (x292 != 0) {
        // loc("zirgen/components/ram.cpp":111:43)
        auto x293 = x178 - x242;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x293 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x294 = x179 - x243;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x294 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x295 = x180 - x244;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x295 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x296 = x181 - x245;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x296 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
      }
    }
    // loc("Top/mux(Mux)/ram_load(RamLoadStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x297 = arg2[91 * steps + ((cycle - 0) & mask)];
    assert(x297 != Fp::invalid());
    // loc("zirgen/components/ram.cpp":115:17)
    auto x298 = x6 - x297;
    // loc("zirgen/components/ram.cpp":114:18)
    auto x299 = x7 - x297;
    // loc("zirgen/components/ram.cpp":115:54)
    auto x300 = x5 - x297;
    // loc("zirgen/components/ram.cpp":115:16)
    auto x301 = x298 * x300;
    // loc("zirgen/components/ram.cpp":114:17)
    auto x302 = x299 * x298;
    // loc("zirgen/components/ram.cpp":116:18)
    auto x303 = x299 * x300;
    if (x303 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[97 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x6);
        reg = x6;
      }
    }
    if (x302 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[97 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x7);
        reg = x7;
      }
    }
    if (x301 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[97 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x246);
        reg = x246;
      }
    }
  }
  if (x10 != 0) {
    {
      extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
      auto x304 = extern_outs[0];
      auto x305 = extern_outs[1];
      auto x306 = extern_outs[2];
      auto x307 = extern_outs[3];
      auto x308 = extern_outs[4];
      auto x309 = extern_outs[5];
      auto x310 = extern_outs[6];
      // loc("zirgen/components/ram.cpp":46:3)
      {
        auto& reg = arg2[146 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x304);
        reg = x304;
      }
      // loc("zirgen/components/ram.cpp":47:3)
      {
        auto& reg = arg2[147 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x305);
        reg = x305;
      }
      // loc("zirgen/components/ram.cpp":48:3)
      {
        auto& reg = arg2[148 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x306);
        reg = x306;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[149 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x307);
        reg = x307;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[150 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x308);
        reg = x308;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[151 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x309);
        reg = x309;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[152 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x310);
        reg = x310;
      }
      extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
      auto x311 = extern_outs[0];
      auto x312 = extern_outs[1];
      auto x313 = extern_outs[2];
      auto x314 = extern_outs[3];
      auto x315 = extern_outs[4];
      auto x316 = extern_outs[5];
      auto x317 = extern_outs[6];
      // loc("zirgen/components/ram.cpp":46:3)
      {
        auto& reg = arg2[153 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x311);
        reg = x311;
      }
      // loc("zirgen/components/ram.cpp":47:3)
      {
        auto& reg = arg2[154 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x312);
        reg = x312;
      }
      // loc("zirgen/components/ram.cpp":48:3)
      {
        auto& reg = arg2[155 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x313);
        reg = x313;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[156 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x314);
        reg = x314;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[157 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x315);
        reg = x315;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[158 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x316);
        reg = x316;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[159 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x317);
        reg = x317;
      }
      extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
      auto x318 = extern_outs[0];
      auto x319 = extern_outs[1];
      auto x320 = extern_outs[2];
      auto x321 = extern_outs[3];
      auto x322 = extern_outs[4];
      auto x323 = extern_outs[5];
      auto x324 = extern_outs[6];
      // loc("zirgen/components/ram.cpp":46:3)
      {
        auto& reg = arg2[160 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x318);
        reg = x318;
      }
      // loc("zirgen/components/ram.cpp":47:3)
      {
        auto& reg = arg2[161 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x319);
        reg = x319;
      }
      // loc("zirgen/components/ram.cpp":48:3)
      {
        auto& reg = arg2[162 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x320);
        reg = x320;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[163 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x321);
        reg = x321;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[164 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x322);
        reg = x322;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[165 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x323);
        reg = x323;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[166 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x324);
        reg = x324;
      }
      extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
      auto x325 = extern_outs[0];
      auto x326 = extern_outs[1];
      auto x327 = extern_outs[2];
      auto x328 = extern_outs[3];
      auto x329 = extern_outs[4];
      auto x330 = extern_outs[5];
      auto x331 = extern_outs[6];
      // loc("zirgen/components/ram.cpp":46:3)
      {
        auto& reg = arg2[89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x325);
        reg = x325;
      }
      // loc("zirgen/components/ram.cpp":47:3)
      {
        auto& reg = arg2[90 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x326);
        reg = x326;
      }
      // loc("zirgen/components/ram.cpp":48:3)
      {
        auto& reg = arg2[91 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x327);
        reg = x327;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[92 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x328);
        reg = x328;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[93 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x329);
        reg = x329;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[94 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x330);
        reg = x330;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[95 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x331);
        reg = x331;
      }
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/Global/sys_exit_code(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x332 = arg1[104];
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x333 = arg2[149 * steps + ((cycle - 0) & mask)];
    assert(x333 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x334 = arg2[150 * steps + ((cycle - 0) & mask)];
    assert(x334 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x335 = arg2[151 * steps + ((cycle - 0) & mask)];
    assert(x335 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x336 = arg2[152 * steps + ((cycle - 0) & mask)];
    assert(x336 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
    auto x337 = arg2[90 * steps + ((cycle - 1) & mask)];
    assert(x337 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x338 = arg2[92 * steps + ((cycle - 1) & mask)];
    assert(x338 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x339 = arg2[93 * steps + ((cycle - 1) & mask)];
    assert(x339 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x340 = arg2[94 * steps + ((cycle - 1) & mask)];
    assert(x340 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x341 = arg2[95 * steps + ((cycle - 1) & mask)];
    assert(x341 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("zirgen/components/ram.cpp":65:40))
    auto x342 = arg2[89 * steps + ((cycle - 1) & mask)];
    assert(x342 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("zirgen/components/ram.cpp":67:42))
    auto x343 = arg2[91 * steps + ((cycle - 1) & mask)];
    assert(x343 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x344 = arg2[97 * steps + ((cycle - 1) & mask)];
    assert(x344 != Fp::invalid());
    {
      // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x345 = arg2[146 * steps + ((cycle - 0) & mask)];
      assert(x345 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":85:35)
      auto x346 = x342 - x345;
      // loc("zirgen/components/ram.cpp":85:35)
      auto x347 = (x346 == 0) ? Fp(1) : Fp(0);
      // loc("zirgen/components/ram.cpp":85:27)
      auto x348 = x7 - x347;
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[167 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x348);
        reg = x348;
      }
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x349 = arg2[167 * steps + ((cycle - 0) & mask)];
    assert(x349 != Fp::invalid());
    if (x349 != 0) {
      // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x350 = arg2[148 * steps + ((cycle - 0) & mask)];
      assert(x350 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":97:9)
      auto x351 = x6 - x350;
      // loc("zirgen/components/ram.cpp":97:9)
      assert(x351 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
      // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x352 = arg2[146 * steps + ((cycle - 0) & mask)];
      assert(x352 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":99:17)
      auto x353 = x352 - x342;
      // loc("zirgen/components/ram.cpp":99:17)
      auto x354 = x353 - x7;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x355 = Fp(x354.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[9 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x355);
          reg = x355;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x356 = arg2[9 * steps + ((cycle - 0) & mask)];
      assert(x356 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x357 = x354 - x356;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x358 = x357 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x359 = Fp(x358.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[10 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x359);
          reg = x359;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x360 = arg2[10 * steps + ((cycle - 0) & mask)];
      assert(x360 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x361 = x358 - x360;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x362 = x361 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x363 = Fp(x362.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[11 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x363);
          reg = x363;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x364 = arg2[11 * steps + ((cycle - 0) & mask)];
      assert(x364 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x365 = x362 - x364;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x366 = x365 * x3;
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x366);
        reg = x366;
      }
      // loc("zirgen/components/ram.cpp":101:9)
      auto x367 = x332 * x344;
      // loc("zirgen/components/ram.cpp":101:9)
      assert(x367 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
    }
    // loc("zirgen/components/ram.cpp":105:19)
    auto x368 = x7 - x349;
    if (x368 != 0) {
      // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x369 = arg2[146 * steps + ((cycle - 0) & mask)];
      assert(x369 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":107:9)
      auto x370 = x342 - x369;
      // loc("zirgen/components/ram.cpp":107:9)
      assert(x370 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
      // loc("zirgen/components/ram.cpp":109:43)
      auto x371 = x337 * x2;
      // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x372 = arg2[147 * steps + ((cycle - 0) & mask)];
      assert(x372 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x373 = arg2[148 * steps + ((cycle - 0) & mask)];
      assert(x373 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":109:17)
      auto x374 = x372 * x2;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x375 = x374 + x373;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x376 = x375 - x371;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x377 = x376 + x343;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x378 = Fp(x377.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[9 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x378);
          reg = x378;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x379 = arg2[9 * steps + ((cycle - 0) & mask)];
      assert(x379 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x380 = x377 - x379;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x381 = x380 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x382 = Fp(x381.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[10 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x382);
          reg = x382;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x383 = arg2[10 * steps + ((cycle - 0) & mask)];
      assert(x383 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x384 = x381 - x383;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x385 = x384 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x386 = Fp(x385.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[11 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x386);
          reg = x386;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x387 = arg2[11 * steps + ((cycle - 0) & mask)];
      assert(x387 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x388 = x385 - x387;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x389 = x388 * x3;
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x389);
        reg = x389;
      }
      // loc("zirgen/components/ram.cpp":111:39)
      auto x390 = x5 - x373;
      if (x390 != 0) {
        // loc("zirgen/components/ram.cpp":111:43)
        auto x391 = x338 - x333;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x391 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x392 = x339 - x334;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x392 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x393 = x340 - x335;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x393 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x394 = x341 - x336;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x394 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
      }
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x395 = arg2[148 * steps + ((cycle - 0) & mask)];
    assert(x395 != Fp::invalid());
    // loc("zirgen/components/ram.cpp":115:17)
    auto x396 = x6 - x395;
    // loc("zirgen/components/ram.cpp":114:18)
    auto x397 = x7 - x395;
    // loc("zirgen/components/ram.cpp":115:54)
    auto x398 = x5 - x395;
    // loc("zirgen/components/ram.cpp":115:16)
    auto x399 = x396 * x398;
    // loc("zirgen/components/ram.cpp":114:17)
    auto x400 = x397 * x396;
    // loc("zirgen/components/ram.cpp":116:18)
    auto x401 = x397 * x398;
    if (x401 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[168 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x6);
        reg = x6;
      }
    }
    if (x400 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[168 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x7);
        reg = x7;
      }
    }
    if (x399 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[168 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x344);
        reg = x344;
      }
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
    auto x402 = arg2[147 * steps + ((cycle - 0) & mask)];
    assert(x402 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
    auto x403 = arg2[146 * steps + ((cycle - 0) & mask)];
    assert(x403 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x404 = arg2[156 * steps + ((cycle - 0) & mask)];
    assert(x404 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x405 = arg2[157 * steps + ((cycle - 0) & mask)];
    assert(x405 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x406 = arg2[158 * steps + ((cycle - 0) & mask)];
    assert(x406 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x407 = arg2[159 * steps + ((cycle - 0) & mask)];
    assert(x407 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x408 = arg2[168 * steps + ((cycle - 0) & mask)];
    assert(x408 != Fp::invalid());
    {
      // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x409 = arg2[153 * steps + ((cycle - 0) & mask)];
      assert(x409 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":85:35)
      auto x410 = x403 - x409;
      // loc("zirgen/components/ram.cpp":85:35)
      auto x411 = (x410 == 0) ? Fp(1) : Fp(0);
      // loc("zirgen/components/ram.cpp":85:27)
      auto x412 = x7 - x411;
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[169 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x412);
        reg = x412;
      }
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x413 = arg2[169 * steps + ((cycle - 0) & mask)];
    assert(x413 != Fp::invalid());
    if (x413 != 0) {
      // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x414 = arg2[155 * steps + ((cycle - 0) & mask)];
      assert(x414 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":97:9)
      auto x415 = x6 - x414;
      // loc("zirgen/components/ram.cpp":97:9)
      assert(x415 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
      // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x416 = arg2[153 * steps + ((cycle - 0) & mask)];
      assert(x416 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":99:17)
      auto x417 = x416 - x403;
      // loc("zirgen/components/ram.cpp":99:17)
      auto x418 = x417 - x7;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x419 = Fp(x418.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[12 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x419);
          reg = x419;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x420 = arg2[12 * steps + ((cycle - 0) & mask)];
      assert(x420 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x421 = x418 - x420;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x422 = x421 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x423 = Fp(x422.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[13 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x423);
          reg = x423;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x424 = arg2[13 * steps + ((cycle - 0) & mask)];
      assert(x424 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x425 = x422 - x424;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x426 = x425 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x427 = Fp(x426.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[14 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x427);
          reg = x427;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x428 = arg2[14 * steps + ((cycle - 0) & mask)];
      assert(x428 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x429 = x426 - x428;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x430 = x429 * x3;
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[73 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x430);
        reg = x430;
      }
      // loc("zirgen/components/ram.cpp":101:9)
      auto x431 = x332 * x408;
      // loc("zirgen/components/ram.cpp":101:9)
      assert(x431 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
    }
    // loc("zirgen/components/ram.cpp":105:19)
    auto x432 = x7 - x413;
    if (x432 != 0) {
      // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x433 = arg2[153 * steps + ((cycle - 0) & mask)];
      assert(x433 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":107:9)
      auto x434 = x403 - x433;
      // loc("zirgen/components/ram.cpp":107:9)
      assert(x434 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
      // loc("zirgen/components/ram.cpp":109:43)
      auto x435 = x402 * x2;
      // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x436 = arg2[154 * steps + ((cycle - 0) & mask)];
      assert(x436 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x437 = arg2[155 * steps + ((cycle - 0) & mask)];
      assert(x437 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":109:17)
      auto x438 = x436 * x2;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x439 = x438 + x437;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x440 = x439 - x435;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x441 = x440 + x395;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x442 = Fp(x441.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[12 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x442);
          reg = x442;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x443 = arg2[12 * steps + ((cycle - 0) & mask)];
      assert(x443 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x444 = x441 - x443;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x445 = x444 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x446 = Fp(x445.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[13 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x446);
          reg = x446;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x447 = arg2[13 * steps + ((cycle - 0) & mask)];
      assert(x447 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x448 = x445 - x447;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x449 = x448 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x450 = Fp(x449.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[14 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x450);
          reg = x450;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x451 = arg2[14 * steps + ((cycle - 0) & mask)];
      assert(x451 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x452 = x449 - x451;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x453 = x452 * x3;
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[73 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x453);
        reg = x453;
      }
      // loc("zirgen/components/ram.cpp":111:39)
      auto x454 = x5 - x437;
      if (x454 != 0) {
        // loc("zirgen/components/ram.cpp":111:43)
        auto x455 = x333 - x404;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x455 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x456 = x334 - x405;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x456 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x457 = x335 - x406;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x457 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x458 = x336 - x407;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x458 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
      }
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x459 = arg2[155 * steps + ((cycle - 0) & mask)];
    assert(x459 != Fp::invalid());
    // loc("zirgen/components/ram.cpp":115:17)
    auto x460 = x6 - x459;
    // loc("zirgen/components/ram.cpp":114:18)
    auto x461 = x7 - x459;
    // loc("zirgen/components/ram.cpp":115:54)
    auto x462 = x5 - x459;
    // loc("zirgen/components/ram.cpp":115:16)
    auto x463 = x460 * x462;
    // loc("zirgen/components/ram.cpp":114:17)
    auto x464 = x461 * x460;
    // loc("zirgen/components/ram.cpp":116:18)
    auto x465 = x461 * x462;
    if (x465 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[170 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x6);
        reg = x6;
      }
    }
    if (x464 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[170 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x7);
        reg = x7;
      }
    }
    if (x463 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[170 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x408);
        reg = x408;
      }
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
    auto x466 = arg2[154 * steps + ((cycle - 0) & mask)];
    assert(x466 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
    auto x467 = arg2[153 * steps + ((cycle - 0) & mask)];
    assert(x467 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x468 = arg2[163 * steps + ((cycle - 0) & mask)];
    assert(x468 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x469 = arg2[164 * steps + ((cycle - 0) & mask)];
    assert(x469 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x470 = arg2[165 * steps + ((cycle - 0) & mask)];
    assert(x470 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x471 = arg2[166 * steps + ((cycle - 0) & mask)];
    assert(x471 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x472 = arg2[170 * steps + ((cycle - 0) & mask)];
    assert(x472 != Fp::invalid());
    {
      // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x473 = arg2[160 * steps + ((cycle - 0) & mask)];
      assert(x473 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":85:35)
      auto x474 = x467 - x473;
      // loc("zirgen/components/ram.cpp":85:35)
      auto x475 = (x474 == 0) ? Fp(1) : Fp(0);
      // loc("zirgen/components/ram.cpp":85:27)
      auto x476 = x7 - x475;
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[171 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x476);
        reg = x476;
      }
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x477 = arg2[171 * steps + ((cycle - 0) & mask)];
    assert(x477 != Fp::invalid());
    if (x477 != 0) {
      // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x478 = arg2[162 * steps + ((cycle - 0) & mask)];
      assert(x478 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":97:9)
      auto x479 = x6 - x478;
      // loc("zirgen/components/ram.cpp":97:9)
      assert(x479 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
      // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x480 = arg2[160 * steps + ((cycle - 0) & mask)];
      assert(x480 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":99:17)
      auto x481 = x480 - x467;
      // loc("zirgen/components/ram.cpp":99:17)
      auto x482 = x481 - x7;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x483 = Fp(x482.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[15 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x483);
          reg = x483;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x484 = arg2[15 * steps + ((cycle - 0) & mask)];
      assert(x484 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x485 = x482 - x484;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x486 = x485 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x487 = Fp(x486.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[16 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x487);
          reg = x487;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x488 = arg2[16 * steps + ((cycle - 0) & mask)];
      assert(x488 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x489 = x486 - x488;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x490 = x489 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x491 = Fp(x490.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[17 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x491);
          reg = x491;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x492 = arg2[17 * steps + ((cycle - 0) & mask)];
      assert(x492 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x493 = x490 - x492;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x494 = x493 * x3;
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x494);
        reg = x494;
      }
      // loc("zirgen/components/ram.cpp":101:9)
      auto x495 = x332 * x472;
      // loc("zirgen/components/ram.cpp":101:9)
      assert(x495 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
    }
    // loc("zirgen/components/ram.cpp":105:19)
    auto x496 = x7 - x477;
    if (x496 != 0) {
      // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x497 = arg2[160 * steps + ((cycle - 0) & mask)];
      assert(x497 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":107:9)
      auto x498 = x467 - x497;
      // loc("zirgen/components/ram.cpp":107:9)
      assert(x498 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
      // loc("zirgen/components/ram.cpp":109:43)
      auto x499 = x466 * x2;
      // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x500 = arg2[161 * steps + ((cycle - 0) & mask)];
      assert(x500 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x501 = arg2[162 * steps + ((cycle - 0) & mask)];
      assert(x501 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":109:17)
      auto x502 = x500 * x2;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x503 = x502 + x501;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x504 = x503 - x499;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x505 = x504 + x459;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x506 = Fp(x505.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[15 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x506);
          reg = x506;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x507 = arg2[15 * steps + ((cycle - 0) & mask)];
      assert(x507 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x508 = x505 - x507;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x509 = x508 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x510 = Fp(x509.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[16 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x510);
          reg = x510;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x511 = arg2[16 * steps + ((cycle - 0) & mask)];
      assert(x511 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x512 = x509 - x511;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x513 = x512 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x514 = Fp(x513.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[17 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x514);
          reg = x514;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x515 = arg2[17 * steps + ((cycle - 0) & mask)];
      assert(x515 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x516 = x513 - x515;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x517 = x516 * x3;
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x517);
        reg = x517;
      }
      // loc("zirgen/components/ram.cpp":111:39)
      auto x518 = x5 - x501;
      if (x518 != 0) {
        // loc("zirgen/components/ram.cpp":111:43)
        auto x519 = x404 - x468;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x519 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x520 = x405 - x469;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x520 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x521 = x406 - x470;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x521 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x522 = x407 - x471;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x522 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
      }
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x523 = arg2[162 * steps + ((cycle - 0) & mask)];
    assert(x523 != Fp::invalid());
    // loc("zirgen/components/ram.cpp":115:17)
    auto x524 = x6 - x523;
    // loc("zirgen/components/ram.cpp":114:18)
    auto x525 = x7 - x523;
    // loc("zirgen/components/ram.cpp":115:54)
    auto x526 = x5 - x523;
    // loc("zirgen/components/ram.cpp":115:16)
    auto x527 = x524 * x526;
    // loc("zirgen/components/ram.cpp":114:17)
    auto x528 = x525 * x524;
    // loc("zirgen/components/ram.cpp":116:18)
    auto x529 = x525 * x526;
    if (x529 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[172 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x6);
        reg = x6;
      }
    }
    if (x528 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[172 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x7);
        reg = x7;
      }
    }
    if (x527 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[172 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x472);
        reg = x472;
      }
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
    auto x530 = arg2[161 * steps + ((cycle - 0) & mask)];
    assert(x530 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
    auto x531 = arg2[160 * steps + ((cycle - 0) & mask)];
    assert(x531 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x532 = arg2[92 * steps + ((cycle - 0) & mask)];
    assert(x532 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x533 = arg2[93 * steps + ((cycle - 0) & mask)];
    assert(x533 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x534 = arg2[94 * steps + ((cycle - 0) & mask)];
    assert(x534 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x535 = arg2[95 * steps + ((cycle - 0) & mask)];
    assert(x535 != Fp::invalid());
    // loc("Top/mux(Mux)/reset(ResetStep)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x536 = arg2[172 * steps + ((cycle - 0) & mask)];
    assert(x536 != Fp::invalid());
    {
      // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x537 = arg2[89 * steps + ((cycle - 0) & mask)];
      assert(x537 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":85:35)
      auto x538 = x531 - x537;
      // loc("zirgen/components/ram.cpp":85:35)
      auto x539 = (x538 == 0) ? Fp(1) : Fp(0);
      // loc("zirgen/components/ram.cpp":85:27)
      auto x540 = x7 - x539;
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[96 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x540);
        reg = x540;
      }
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x541 = arg2[96 * steps + ((cycle - 0) & mask)];
    assert(x541 != Fp::invalid());
    if (x541 != 0) {
      // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x542 = arg2[91 * steps + ((cycle - 0) & mask)];
      assert(x542 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":97:9)
      auto x543 = x6 - x542;
      // loc("zirgen/components/ram.cpp":97:9)
      assert(x543 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
      // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x544 = arg2[89 * steps + ((cycle - 0) & mask)];
      assert(x544 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":99:17)
      auto x545 = x544 - x531;
      // loc("zirgen/components/ram.cpp":99:17)
      auto x546 = x545 - x7;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x547 = Fp(x546.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x547);
          reg = x547;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x548 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x548 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x549 = x546 - x548;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x550 = x549 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x551 = Fp(x550.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x551);
          reg = x551;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x552 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x552 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x553 = x550 - x552;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x554 = x553 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x555 = Fp(x554.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x555);
          reg = x555;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x556 = arg2[5 * steps + ((cycle - 0) & mask)];
      assert(x556 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x557 = x554 - x556;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x558 = x557 * x3;
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x558);
        reg = x558;
      }
      // loc("zirgen/components/ram.cpp":101:9)
      auto x559 = x332 * x536;
      // loc("zirgen/components/ram.cpp":101:9)
      assert(x559 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
    }
    // loc("zirgen/components/ram.cpp":105:19)
    auto x560 = x7 - x541;
    if (x560 != 0) {
      // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x561 = arg2[89 * steps + ((cycle - 0) & mask)];
      assert(x561 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":107:9)
      auto x562 = x531 - x561;
      // loc("zirgen/components/ram.cpp":107:9)
      assert(x562 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
      // loc("zirgen/components/ram.cpp":109:43)
      auto x563 = x530 * x2;
      // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x564 = arg2[90 * steps + ((cycle - 0) & mask)];
      assert(x564 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x565 = arg2[91 * steps + ((cycle - 0) & mask)];
      assert(x565 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":109:17)
      auto x566 = x564 * x2;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x567 = x566 + x565;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x568 = x567 - x563;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x569 = x568 + x523;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x570 = Fp(x569.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x570);
          reg = x570;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x571 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x571 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x572 = x569 - x571;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x573 = x572 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x574 = Fp(x573.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x574);
          reg = x574;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x575 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x575 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x576 = x573 - x575;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x577 = x576 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x578 = Fp(x577.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x578);
          reg = x578;
        }
      }
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x579 = arg2[5 * steps + ((cycle - 0) & mask)];
      assert(x579 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x580 = x577 - x579;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x581 = x580 * x3;
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x581);
        reg = x581;
      }
      // loc("zirgen/components/ram.cpp":111:39)
      auto x582 = x5 - x565;
      if (x582 != 0) {
        // loc("zirgen/components/ram.cpp":111:43)
        auto x583 = x468 - x532;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x583 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x584 = x469 - x533;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x584 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x585 = x470 - x534;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x585 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x586 = x471 - x535;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x586 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
      }
    }
    // loc("Top/mux(Mux)/reset(ResetStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x587 = arg2[91 * steps + ((cycle - 0) & mask)];
    assert(x587 != Fp::invalid());
    // loc("zirgen/components/ram.cpp":115:17)
    auto x588 = x6 - x587;
    // loc("zirgen/components/ram.cpp":114:18)
    auto x589 = x7 - x587;
    // loc("zirgen/components/ram.cpp":115:54)
    auto x590 = x5 - x587;
    // loc("zirgen/components/ram.cpp":115:16)
    auto x591 = x588 * x590;
    // loc("zirgen/components/ram.cpp":114:17)
    auto x592 = x589 * x588;
    // loc("zirgen/components/ram.cpp":116:18)
    auto x593 = x589 * x590;
    if (x593 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[97 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x6);
        reg = x6;
      }
    }
    if (x592 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[97 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x7);
        reg = x7;
      }
    }
    if (x591 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[97 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x536);
        reg = x536;
      }
    }
  }
  if (x11 != 0) {
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x594 = arg2[101 * steps + ((cycle - 0) & mask)];
    assert(x594 != Fp::invalid());
    if (x594 != 0) {
      {
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x595 = extern_outs[0];
        auto x596 = extern_outs[1];
        auto x597 = extern_outs[2];
        auto x598 = extern_outs[3];
        auto x599 = extern_outs[4];
        auto x600 = extern_outs[5];
        auto x601 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x595);
          reg = x595;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x596);
          reg = x596;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x597);
          reg = x597;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x598);
          reg = x598;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x599);
          reg = x599;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x600);
          reg = x600;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x601);
          reg = x601;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x602 = extern_outs[0];
        auto x603 = extern_outs[1];
        auto x604 = extern_outs[2];
        auto x605 = extern_outs[3];
        auto x606 = extern_outs[4];
        auto x607 = extern_outs[5];
        auto x608 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x602);
          reg = x602;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x603);
          reg = x603;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x604);
          reg = x604;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x605);
          reg = x605;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x606);
          reg = x606;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x607);
          reg = x607;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x608);
          reg = x608;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x609 = extern_outs[0];
        auto x610 = extern_outs[1];
        auto x611 = extern_outs[2];
        auto x612 = extern_outs[3];
        auto x613 = extern_outs[4];
        auto x614 = extern_outs[5];
        auto x615 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x609);
          reg = x609;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[161 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x610);
          reg = x610;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[162 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x611);
          reg = x611;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[163 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x612);
          reg = x612;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[164 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x613);
          reg = x613;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[165 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x614);
          reg = x614;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[166 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x615);
          reg = x615;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x616 = extern_outs[0];
        auto x617 = extern_outs[1];
        auto x618 = extern_outs[2];
        auto x619 = extern_outs[3];
        auto x620 = extern_outs[4];
        auto x621 = extern_outs[5];
        auto x622 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[89 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x616);
          reg = x616;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[90 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x617);
          reg = x617;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[91 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x618);
          reg = x618;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[92 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x619);
          reg = x619;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[93 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x620);
          reg = x620;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[94 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x621);
          reg = x621;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[95 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x622);
          reg = x622;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/global(Global)/sys_exit_code(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x623 = arg1[104];
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x624 = arg2[149 * steps + ((cycle - 0) & mask)];
      assert(x624 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x625 = arg2[150 * steps + ((cycle - 0) & mask)];
      assert(x625 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x626 = arg2[151 * steps + ((cycle - 0) & mask)];
      assert(x626 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x627 = arg2[152 * steps + ((cycle - 0) & mask)];
      assert(x627 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x628 = arg2[90 * steps + ((cycle - 1) & mask)];
      assert(x628 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x629 = arg2[92 * steps + ((cycle - 1) & mask)];
      assert(x629 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x630 = arg2[93 * steps + ((cycle - 1) & mask)];
      assert(x630 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x631 = arg2[94 * steps + ((cycle - 1) & mask)];
      assert(x631 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x632 = arg2[95 * steps + ((cycle - 1) & mask)];
      assert(x632 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x633 = arg2[89 * steps + ((cycle - 1) & mask)];
      assert(x633 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("zirgen/components/ram.cpp":67:42))
      auto x634 = arg2[91 * steps + ((cycle - 1) & mask)];
      assert(x634 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x635 = arg2[97 * steps + ((cycle - 1) & mask)];
      assert(x635 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x636 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x636 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x637 = x633 - x636;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x638 = (x637 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x639 = x7 - x638;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[167 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x639);
          reg = x639;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x640 = arg2[167 * steps + ((cycle - 0) & mask)];
      assert(x640 != Fp::invalid());
      if (x640 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x641 = arg2[148 * steps + ((cycle - 0) & mask)];
        assert(x641 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x642 = x6 - x641;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x642 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x643 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x643 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x644 = x643 - x633;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x645 = x644 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x646 = Fp(x645.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x646);
            reg = x646;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x647 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x647 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x648 = x645 - x647;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x649 = x648 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x650 = Fp(x649.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x650);
            reg = x650;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x651 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x651 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x652 = x649 - x651;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x653 = x652 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x654 = Fp(x653.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x654);
            reg = x654;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x655 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x655 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x656 = x653 - x655;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x657 = x656 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x657);
          reg = x657;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x658 = x623 * x635;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x658 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x659 = x7 - x640;
      if (x659 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x660 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x660 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x661 = x633 - x660;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x661 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x662 = x628 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x663 = arg2[147 * steps + ((cycle - 0) & mask)];
        assert(x663 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x664 = arg2[148 * steps + ((cycle - 0) & mask)];
        assert(x664 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x665 = x663 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x666 = x665 + x664;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x667 = x666 - x662;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x668 = x667 + x634;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x669 = Fp(x668.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x669);
            reg = x669;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x670 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x670 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x671 = x668 - x670;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x672 = x671 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x673 = Fp(x672.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x673);
            reg = x673;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x674 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x674 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x675 = x672 - x674;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x676 = x675 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x677 = Fp(x676.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x677);
            reg = x677;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x678 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x678 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x679 = x676 - x678;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x680 = x679 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x680);
          reg = x680;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x681 = x5 - x664;
        if (x681 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x682 = x629 - x624;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x682 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x683 = x630 - x625;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x683 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x684 = x631 - x626;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x684 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x685 = x632 - x627;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x685 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x686 = arg2[148 * steps + ((cycle - 0) & mask)];
      assert(x686 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x687 = x6 - x686;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x688 = x7 - x686;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x689 = x5 - x686;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x690 = x687 * x689;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x691 = x688 * x687;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x692 = x688 * x689;
      if (x692 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x691 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x690 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x635);
          reg = x635;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x693 = arg2[147 * steps + ((cycle - 0) & mask)];
      assert(x693 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x694 = arg2[146 * steps + ((cycle - 0) & mask)];
      assert(x694 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x695 = arg2[156 * steps + ((cycle - 0) & mask)];
      assert(x695 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x696 = arg2[157 * steps + ((cycle - 0) & mask)];
      assert(x696 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x697 = arg2[158 * steps + ((cycle - 0) & mask)];
      assert(x697 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x698 = arg2[159 * steps + ((cycle - 0) & mask)];
      assert(x698 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x699 = arg2[168 * steps + ((cycle - 0) & mask)];
      assert(x699 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x700 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x700 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x701 = x694 - x700;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x702 = (x701 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x703 = x7 - x702;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[169 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x703);
          reg = x703;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x704 = arg2[169 * steps + ((cycle - 0) & mask)];
      assert(x704 != Fp::invalid());
      if (x704 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x705 = arg2[155 * steps + ((cycle - 0) & mask)];
        assert(x705 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x706 = x6 - x705;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x706 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x707 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x707 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x708 = x707 - x694;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x709 = x708 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x710 = Fp(x709.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x710);
            reg = x710;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x711 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x711 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x712 = x709 - x711;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x713 = x712 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x714 = Fp(x713.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x714);
            reg = x714;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x715 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x715 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x716 = x713 - x715;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x717 = x716 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x718 = Fp(x717.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x718);
            reg = x718;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x719 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x719 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x720 = x717 - x719;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x721 = x720 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x721);
          reg = x721;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x722 = x623 * x699;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x722 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x723 = x7 - x704;
      if (x723 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x724 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x724 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x725 = x694 - x724;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x725 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x726 = x693 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x727 = arg2[154 * steps + ((cycle - 0) & mask)];
        assert(x727 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x728 = arg2[155 * steps + ((cycle - 0) & mask)];
        assert(x728 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x729 = x727 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x730 = x729 + x728;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x731 = x730 - x726;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x732 = x731 + x686;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x733 = Fp(x732.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x733);
            reg = x733;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x734 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x734 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x735 = x732 - x734;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x736 = x735 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x737 = Fp(x736.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x737);
            reg = x737;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x738 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x738 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x739 = x736 - x738;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x740 = x739 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x741 = Fp(x740.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x741);
            reg = x741;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x742 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x742 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x743 = x740 - x742;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x744 = x743 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x744);
          reg = x744;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x745 = x5 - x728;
        if (x745 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x746 = x624 - x695;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x746 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x747 = x625 - x696;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x747 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x748 = x626 - x697;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x748 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x749 = x627 - x698;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x749 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x750 = arg2[155 * steps + ((cycle - 0) & mask)];
      assert(x750 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x751 = x6 - x750;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x752 = x7 - x750;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x753 = x5 - x750;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x754 = x751 * x753;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x755 = x752 * x751;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x756 = x752 * x753;
      if (x756 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x755 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x754 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x699);
          reg = x699;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x757 = arg2[154 * steps + ((cycle - 0) & mask)];
      assert(x757 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x758 = arg2[153 * steps + ((cycle - 0) & mask)];
      assert(x758 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x759 = arg2[163 * steps + ((cycle - 0) & mask)];
      assert(x759 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x760 = arg2[164 * steps + ((cycle - 0) & mask)];
      assert(x760 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x761 = arg2[165 * steps + ((cycle - 0) & mask)];
      assert(x761 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x762 = arg2[166 * steps + ((cycle - 0) & mask)];
      assert(x762 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x763 = arg2[170 * steps + ((cycle - 0) & mask)];
      assert(x763 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x764 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x764 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x765 = x758 - x764;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x766 = (x765 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x767 = x7 - x766;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[171 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x767);
          reg = x767;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x768 = arg2[171 * steps + ((cycle - 0) & mask)];
      assert(x768 != Fp::invalid());
      if (x768 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x769 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x769 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x770 = x6 - x769;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x770 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x771 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x771 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x772 = x771 - x758;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x773 = x772 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x774 = Fp(x773.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x774);
            reg = x774;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x775 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x775 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x776 = x773 - x775;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x777 = x776 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x778 = Fp(x777.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x778);
            reg = x778;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x779 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x779 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x780 = x777 - x779;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x781 = x780 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x782 = Fp(x781.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x782);
            reg = x782;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x783 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x783 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x784 = x781 - x783;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x785 = x784 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x785);
          reg = x785;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x786 = x623 * x763;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x786 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x787 = x7 - x768;
      if (x787 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x788 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x788 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x789 = x758 - x788;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x789 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x790 = x757 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x791 = arg2[161 * steps + ((cycle - 0) & mask)];
        assert(x791 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x792 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x792 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x793 = x791 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x794 = x793 + x792;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x795 = x794 - x790;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x796 = x795 + x750;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x797 = Fp(x796.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x797);
            reg = x797;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x798 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x798 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x799 = x796 - x798;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x800 = x799 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x801 = Fp(x800.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x801);
            reg = x801;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x802 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x802 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x803 = x800 - x802;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x804 = x803 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x805 = Fp(x804.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x805);
            reg = x805;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x806 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x806 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x807 = x804 - x806;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x808 = x807 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x808);
          reg = x808;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x809 = x5 - x792;
        if (x809 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x810 = x695 - x759;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x810 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x811 = x696 - x760;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x811 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x812 = x697 - x761;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x812 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x813 = x698 - x762;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x813 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x814 = arg2[162 * steps + ((cycle - 0) & mask)];
      assert(x814 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x815 = x6 - x814;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x816 = x7 - x814;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x817 = x5 - x814;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x818 = x815 * x817;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x819 = x816 * x815;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x820 = x816 * x817;
      if (x820 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x819 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x818 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x763);
          reg = x763;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x821 = arg2[161 * steps + ((cycle - 0) & mask)];
      assert(x821 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x822 = arg2[160 * steps + ((cycle - 0) & mask)];
      assert(x822 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x823 = arg2[92 * steps + ((cycle - 0) & mask)];
      assert(x823 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x824 = arg2[93 * steps + ((cycle - 0) & mask)];
      assert(x824 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x825 = arg2[94 * steps + ((cycle - 0) & mask)];
      assert(x825 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x826 = arg2[95 * steps + ((cycle - 0) & mask)];
      assert(x826 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute0(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x827 = arg2[172 * steps + ((cycle - 0) & mask)];
      assert(x827 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x828 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x828 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x829 = x822 - x828;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x830 = (x829 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x831 = x7 - x830;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[96 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x831);
          reg = x831;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x832 = arg2[96 * steps + ((cycle - 0) & mask)];
      assert(x832 != Fp::invalid());
      if (x832 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x833 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x833 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x834 = x6 - x833;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x834 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x835 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x835 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x836 = x835 - x822;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x837 = x836 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x838 = Fp(x837.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x838);
            reg = x838;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x839 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x839 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x840 = x837 - x839;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x841 = x840 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x842 = Fp(x841.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x842);
            reg = x842;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x843 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x843 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x844 = x841 - x843;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x845 = x844 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x846 = Fp(x845.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x846);
            reg = x846;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x847 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x847 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x848 = x845 - x847;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x849 = x848 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x849);
          reg = x849;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x850 = x623 * x827;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x850 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x851 = x7 - x832;
      if (x851 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x852 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x852 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x853 = x822 - x852;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x853 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x854 = x821 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x855 = arg2[90 * steps + ((cycle - 0) & mask)];
        assert(x855 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x856 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x856 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x857 = x855 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x858 = x857 + x856;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x859 = x858 - x854;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x860 = x859 + x814;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x861 = Fp(x860.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x861);
            reg = x861;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x862 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x862 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x863 = x860 - x862;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x864 = x863 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x865 = Fp(x864.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x865);
            reg = x865;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x866 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x866 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x867 = x864 - x866;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x868 = x867 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x869 = Fp(x868.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x869);
            reg = x869;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x870 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x870 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x871 = x868 - x870;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x872 = x871 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x872);
          reg = x872;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x873 = x5 - x856;
        if (x873 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x874 = x759 - x823;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x874 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x875 = x760 - x824;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x875 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x876 = x761 - x825;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x876 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x877 = x762 - x826;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x877 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x878 = arg2[91 * steps + ((cycle - 0) & mask)];
      assert(x878 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x879 = x6 - x878;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x880 = x7 - x878;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x881 = x5 - x878;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x882 = x879 * x881;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x883 = x880 * x879;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x884 = x880 * x881;
      if (x884 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x883 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x882 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x827);
          reg = x827;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x885 = arg2[102 * steps + ((cycle - 0) & mask)];
    assert(x885 != Fp::invalid());
    if (x885 != 0) {
      {
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x886 = extern_outs[0];
        auto x887 = extern_outs[1];
        auto x888 = extern_outs[2];
        auto x889 = extern_outs[3];
        auto x890 = extern_outs[4];
        auto x891 = extern_outs[5];
        auto x892 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x886);
          reg = x886;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x887);
          reg = x887;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x888);
          reg = x888;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x889);
          reg = x889;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x890);
          reg = x890;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x891);
          reg = x891;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x892);
          reg = x892;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x893 = extern_outs[0];
        auto x894 = extern_outs[1];
        auto x895 = extern_outs[2];
        auto x896 = extern_outs[3];
        auto x897 = extern_outs[4];
        auto x898 = extern_outs[5];
        auto x899 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x893);
          reg = x893;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x894);
          reg = x894;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x895);
          reg = x895;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x896);
          reg = x896;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x897);
          reg = x897;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x898);
          reg = x898;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x899);
          reg = x899;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x900 = extern_outs[0];
        auto x901 = extern_outs[1];
        auto x902 = extern_outs[2];
        auto x903 = extern_outs[3];
        auto x904 = extern_outs[4];
        auto x905 = extern_outs[5];
        auto x906 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x900);
          reg = x900;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[161 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x901);
          reg = x901;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[162 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x902);
          reg = x902;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[163 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x903);
          reg = x903;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[164 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x904);
          reg = x904;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[165 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x905);
          reg = x905;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[166 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x906);
          reg = x906;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x907 = extern_outs[0];
        auto x908 = extern_outs[1];
        auto x909 = extern_outs[2];
        auto x910 = extern_outs[3];
        auto x911 = extern_outs[4];
        auto x912 = extern_outs[5];
        auto x913 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[89 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x907);
          reg = x907;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[90 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x908);
          reg = x908;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[91 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x909);
          reg = x909;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[92 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x910);
          reg = x910;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[93 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x911);
          reg = x911;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[94 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x912);
          reg = x912;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[95 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x913);
          reg = x913;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/global(Global)/sys_exit_code(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x914 = arg1[104];
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x915 = arg2[149 * steps + ((cycle - 0) & mask)];
      assert(x915 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x916 = arg2[150 * steps + ((cycle - 0) & mask)];
      assert(x916 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x917 = arg2[151 * steps + ((cycle - 0) & mask)];
      assert(x917 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x918 = arg2[152 * steps + ((cycle - 0) & mask)];
      assert(x918 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x919 = arg2[90 * steps + ((cycle - 1) & mask)];
      assert(x919 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x920 = arg2[92 * steps + ((cycle - 1) & mask)];
      assert(x920 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x921 = arg2[93 * steps + ((cycle - 1) & mask)];
      assert(x921 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x922 = arg2[94 * steps + ((cycle - 1) & mask)];
      assert(x922 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x923 = arg2[95 * steps + ((cycle - 1) & mask)];
      assert(x923 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x924 = arg2[89 * steps + ((cycle - 1) & mask)];
      assert(x924 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("zirgen/components/ram.cpp":67:42))
      auto x925 = arg2[91 * steps + ((cycle - 1) & mask)];
      assert(x925 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x926 = arg2[97 * steps + ((cycle - 1) & mask)];
      assert(x926 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x927 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x927 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x928 = x924 - x927;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x929 = (x928 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x930 = x7 - x929;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[167 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x930);
          reg = x930;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x931 = arg2[167 * steps + ((cycle - 0) & mask)];
      assert(x931 != Fp::invalid());
      if (x931 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x932 = arg2[148 * steps + ((cycle - 0) & mask)];
        assert(x932 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x933 = x6 - x932;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x933 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x934 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x934 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x935 = x934 - x924;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x936 = x935 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x937 = Fp(x936.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x937);
            reg = x937;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x938 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x938 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x939 = x936 - x938;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x940 = x939 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x941 = Fp(x940.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x941);
            reg = x941;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x942 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x942 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x943 = x940 - x942;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x944 = x943 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x945 = Fp(x944.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x945);
            reg = x945;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x946 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x946 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x947 = x944 - x946;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x948 = x947 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x948);
          reg = x948;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x949 = x914 * x926;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x949 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x950 = x7 - x931;
      if (x950 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x951 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x951 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x952 = x924 - x951;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x952 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x953 = x919 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x954 = arg2[147 * steps + ((cycle - 0) & mask)];
        assert(x954 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x955 = arg2[148 * steps + ((cycle - 0) & mask)];
        assert(x955 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x956 = x954 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x957 = x956 + x955;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x958 = x957 - x953;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x959 = x958 + x925;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x960 = Fp(x959.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x960);
            reg = x960;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x961 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x961 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x962 = x959 - x961;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x963 = x962 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x964 = Fp(x963.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x964);
            reg = x964;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x965 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x965 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x966 = x963 - x965;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x967 = x966 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x968 = Fp(x967.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x968);
            reg = x968;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x969 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x969 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x970 = x967 - x969;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x971 = x970 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x971);
          reg = x971;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x972 = x5 - x955;
        if (x972 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x973 = x920 - x915;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x973 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x974 = x921 - x916;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x974 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x975 = x922 - x917;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x975 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x976 = x923 - x918;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x976 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x977 = arg2[148 * steps + ((cycle - 0) & mask)];
      assert(x977 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x978 = x6 - x977;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x979 = x7 - x977;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x980 = x5 - x977;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x981 = x978 * x980;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x982 = x979 * x978;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x983 = x979 * x980;
      if (x983 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x982 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x981 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x926);
          reg = x926;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x984 = arg2[147 * steps + ((cycle - 0) & mask)];
      assert(x984 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x985 = arg2[146 * steps + ((cycle - 0) & mask)];
      assert(x985 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x986 = arg2[156 * steps + ((cycle - 0) & mask)];
      assert(x986 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x987 = arg2[157 * steps + ((cycle - 0) & mask)];
      assert(x987 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x988 = arg2[158 * steps + ((cycle - 0) & mask)];
      assert(x988 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x989 = arg2[159 * steps + ((cycle - 0) & mask)];
      assert(x989 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x990 = arg2[168 * steps + ((cycle - 0) & mask)];
      assert(x990 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x991 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x991 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x992 = x985 - x991;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x993 = (x992 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x994 = x7 - x993;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[169 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x994);
          reg = x994;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x995 = arg2[169 * steps + ((cycle - 0) & mask)];
      assert(x995 != Fp::invalid());
      if (x995 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x996 = arg2[155 * steps + ((cycle - 0) & mask)];
        assert(x996 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x997 = x6 - x996;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x997 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x998 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x998 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x999 = x998 - x985;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1000 = x999 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1001 = Fp(x1000.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1001);
            reg = x1001;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1002 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x1002 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1003 = x1000 - x1002;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1004 = x1003 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1005 = Fp(x1004.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1005);
            reg = x1005;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1006 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x1006 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1007 = x1004 - x1006;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1008 = x1007 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1009 = Fp(x1008.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1009);
            reg = x1009;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1010 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x1010 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1011 = x1008 - x1010;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1012 = x1011 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1012);
          reg = x1012;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x1013 = x914 * x990;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x1013 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x1014 = x7 - x995;
      if (x1014 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1015 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x1015 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x1016 = x985 - x1015;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x1016 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x1017 = x984 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1018 = arg2[154 * steps + ((cycle - 0) & mask)];
        assert(x1018 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1019 = arg2[155 * steps + ((cycle - 0) & mask)];
        assert(x1019 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1020 = x1018 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1021 = x1020 + x1019;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1022 = x1021 - x1017;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1023 = x1022 + x977;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1024 = Fp(x1023.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1024);
            reg = x1024;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1025 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x1025 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1026 = x1023 - x1025;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1027 = x1026 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1028 = Fp(x1027.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1028);
            reg = x1028;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1029 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x1029 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1030 = x1027 - x1029;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1031 = x1030 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1032 = Fp(x1031.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1032);
            reg = x1032;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1033 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x1033 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1034 = x1031 - x1033;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1035 = x1034 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1035);
          reg = x1035;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x1036 = x5 - x1019;
        if (x1036 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1037 = x915 - x986;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1037 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1038 = x916 - x987;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1038 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1039 = x917 - x988;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1039 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1040 = x918 - x989;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1040 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x1041 = arg2[155 * steps + ((cycle - 0) & mask)];
      assert(x1041 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x1042 = x6 - x1041;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x1043 = x7 - x1041;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x1044 = x5 - x1041;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x1045 = x1042 * x1044;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x1046 = x1043 * x1042;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x1047 = x1043 * x1044;
      if (x1047 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x1046 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x1045 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x990);
          reg = x990;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x1048 = arg2[154 * steps + ((cycle - 0) & mask)];
      assert(x1048 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x1049 = arg2[153 * steps + ((cycle - 0) & mask)];
      assert(x1049 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1050 = arg2[163 * steps + ((cycle - 0) & mask)];
      assert(x1050 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1051 = arg2[164 * steps + ((cycle - 0) & mask)];
      assert(x1051 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1052 = arg2[165 * steps + ((cycle - 0) & mask)];
      assert(x1052 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1053 = arg2[166 * steps + ((cycle - 0) & mask)];
      assert(x1053 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1054 = arg2[170 * steps + ((cycle - 0) & mask)];
      assert(x1054 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1055 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x1055 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1056 = x1049 - x1055;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1057 = (x1056 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x1058 = x7 - x1057;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[171 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1058);
          reg = x1058;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1059 = arg2[171 * steps + ((cycle - 0) & mask)];
      assert(x1059 != Fp::invalid());
      if (x1059 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1060 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x1060 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x1061 = x6 - x1060;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x1061 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1062 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x1062 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1063 = x1062 - x1049;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1064 = x1063 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1065 = Fp(x1064.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1065);
            reg = x1065;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1066 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x1066 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1067 = x1064 - x1066;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1068 = x1067 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1069 = Fp(x1068.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1069);
            reg = x1069;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1070 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x1070 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1071 = x1068 - x1070;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1072 = x1071 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1073 = Fp(x1072.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1073);
            reg = x1073;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1074 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x1074 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1075 = x1072 - x1074;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1076 = x1075 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1076);
          reg = x1076;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x1077 = x914 * x1054;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x1077 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x1078 = x7 - x1059;
      if (x1078 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1079 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x1079 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x1080 = x1049 - x1079;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x1080 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x1081 = x1048 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1082 = arg2[161 * steps + ((cycle - 0) & mask)];
        assert(x1082 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1083 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x1083 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1084 = x1082 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1085 = x1084 + x1083;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1086 = x1085 - x1081;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1087 = x1086 + x1041;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1088 = Fp(x1087.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1088);
            reg = x1088;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1089 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x1089 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1090 = x1087 - x1089;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1091 = x1090 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1092 = Fp(x1091.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1092);
            reg = x1092;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1093 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x1093 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1094 = x1091 - x1093;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1095 = x1094 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1096 = Fp(x1095.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1096);
            reg = x1096;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1097 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x1097 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1098 = x1095 - x1097;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1099 = x1098 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1099);
          reg = x1099;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x1100 = x5 - x1083;
        if (x1100 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1101 = x986 - x1050;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1101 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1102 = x987 - x1051;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1102 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1103 = x988 - x1052;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1103 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1104 = x989 - x1053;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1104 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x1105 = arg2[162 * steps + ((cycle - 0) & mask)];
      assert(x1105 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x1106 = x6 - x1105;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x1107 = x7 - x1105;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x1108 = x5 - x1105;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x1109 = x1106 * x1108;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x1110 = x1107 * x1106;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x1111 = x1107 * x1108;
      if (x1111 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x1110 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x1109 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1054);
          reg = x1054;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x1112 = arg2[161 * steps + ((cycle - 0) & mask)];
      assert(x1112 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x1113 = arg2[160 * steps + ((cycle - 0) & mask)];
      assert(x1113 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1114 = arg2[92 * steps + ((cycle - 0) & mask)];
      assert(x1114 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1115 = arg2[93 * steps + ((cycle - 0) & mask)];
      assert(x1115 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1116 = arg2[94 * steps + ((cycle - 0) & mask)];
      assert(x1116 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1117 = arg2[95 * steps + ((cycle - 0) & mask)];
      assert(x1117 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute1(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1118 = arg2[172 * steps + ((cycle - 0) & mask)];
      assert(x1118 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1119 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x1119 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1120 = x1113 - x1119;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1121 = (x1120 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x1122 = x7 - x1121;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[96 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1122);
          reg = x1122;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1123 = arg2[96 * steps + ((cycle - 0) & mask)];
      assert(x1123 != Fp::invalid());
      if (x1123 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1124 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x1124 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x1125 = x6 - x1124;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x1125 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1126 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x1126 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1127 = x1126 - x1113;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1128 = x1127 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1129 = Fp(x1128.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1129);
            reg = x1129;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1130 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x1130 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1131 = x1128 - x1130;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1132 = x1131 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1133 = Fp(x1132.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1133);
            reg = x1133;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1134 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x1134 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1135 = x1132 - x1134;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1136 = x1135 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1137 = Fp(x1136.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1137);
            reg = x1137;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1138 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x1138 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1139 = x1136 - x1138;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1140 = x1139 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1140);
          reg = x1140;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x1141 = x914 * x1118;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x1141 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x1142 = x7 - x1123;
      if (x1142 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1143 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x1143 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x1144 = x1113 - x1143;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x1144 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x1145 = x1112 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1146 = arg2[90 * steps + ((cycle - 0) & mask)];
        assert(x1146 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1147 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x1147 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1148 = x1146 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1149 = x1148 + x1147;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1150 = x1149 - x1145;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1151 = x1150 + x1105;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1152 = Fp(x1151.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1152);
            reg = x1152;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1153 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x1153 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1154 = x1151 - x1153;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1155 = x1154 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1156 = Fp(x1155.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1156);
            reg = x1156;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1157 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x1157 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1158 = x1155 - x1157;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1159 = x1158 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1160 = Fp(x1159.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1160);
            reg = x1160;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1161 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x1161 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1162 = x1159 - x1161;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1163 = x1162 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1163);
          reg = x1163;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x1164 = x5 - x1147;
        if (x1164 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1165 = x1050 - x1114;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1165 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1166 = x1051 - x1115;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1166 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1167 = x1052 - x1116;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1167 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1168 = x1053 - x1117;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1168 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x1169 = arg2[91 * steps + ((cycle - 0) & mask)];
      assert(x1169 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x1170 = x6 - x1169;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x1171 = x7 - x1169;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x1172 = x5 - x1169;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x1173 = x1170 * x1172;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x1174 = x1171 * x1170;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x1175 = x1171 * x1172;
      if (x1175 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x1174 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x1173 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1118);
          reg = x1118;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x1176 = arg2[103 * steps + ((cycle - 0) & mask)];
    assert(x1176 != Fp::invalid());
    if (x1176 != 0) {
      {
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x1177 = extern_outs[0];
        auto x1178 = extern_outs[1];
        auto x1179 = extern_outs[2];
        auto x1180 = extern_outs[3];
        auto x1181 = extern_outs[4];
        auto x1182 = extern_outs[5];
        auto x1183 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1177);
          reg = x1177;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1178);
          reg = x1178;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1179);
          reg = x1179;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1180);
          reg = x1180;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1181);
          reg = x1181;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1182);
          reg = x1182;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1183);
          reg = x1183;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x1184 = extern_outs[0];
        auto x1185 = extern_outs[1];
        auto x1186 = extern_outs[2];
        auto x1187 = extern_outs[3];
        auto x1188 = extern_outs[4];
        auto x1189 = extern_outs[5];
        auto x1190 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1184);
          reg = x1184;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1185);
          reg = x1185;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1186);
          reg = x1186;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1187);
          reg = x1187;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1188);
          reg = x1188;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1189);
          reg = x1189;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1190);
          reg = x1190;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x1191 = extern_outs[0];
        auto x1192 = extern_outs[1];
        auto x1193 = extern_outs[2];
        auto x1194 = extern_outs[3];
        auto x1195 = extern_outs[4];
        auto x1196 = extern_outs[5];
        auto x1197 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1191);
          reg = x1191;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[161 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1192);
          reg = x1192;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[162 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1193);
          reg = x1193;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[163 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1194);
          reg = x1194;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[164 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1195);
          reg = x1195;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[165 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1196);
          reg = x1196;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[166 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1197);
          reg = x1197;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x1198 = extern_outs[0];
        auto x1199 = extern_outs[1];
        auto x1200 = extern_outs[2];
        auto x1201 = extern_outs[3];
        auto x1202 = extern_outs[4];
        auto x1203 = extern_outs[5];
        auto x1204 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[89 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1198);
          reg = x1198;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[90 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1199);
          reg = x1199;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[91 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1200);
          reg = x1200;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[92 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1201);
          reg = x1201;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[93 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1202);
          reg = x1202;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[94 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1203);
          reg = x1203;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[95 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1204);
          reg = x1204;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/global(Global)/sys_exit_code(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1205 = arg1[104];
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1206 = arg2[149 * steps + ((cycle - 0) & mask)];
      assert(x1206 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1207 = arg2[150 * steps + ((cycle - 0) & mask)];
      assert(x1207 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1208 = arg2[151 * steps + ((cycle - 0) & mask)];
      assert(x1208 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1209 = arg2[152 * steps + ((cycle - 0) & mask)];
      assert(x1209 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x1210 = arg2[90 * steps + ((cycle - 1) & mask)];
      assert(x1210 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1211 = arg2[92 * steps + ((cycle - 1) & mask)];
      assert(x1211 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1212 = arg2[93 * steps + ((cycle - 1) & mask)];
      assert(x1212 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1213 = arg2[94 * steps + ((cycle - 1) & mask)];
      assert(x1213 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1214 = arg2[95 * steps + ((cycle - 1) & mask)];
      assert(x1214 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x1215 = arg2[89 * steps + ((cycle - 1) & mask)];
      assert(x1215 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("zirgen/components/ram.cpp":67:42))
      auto x1216 = arg2[91 * steps + ((cycle - 1) & mask)];
      assert(x1216 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1217 = arg2[97 * steps + ((cycle - 1) & mask)];
      assert(x1217 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1218 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x1218 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1219 = x1215 - x1218;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1220 = (x1219 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x1221 = x7 - x1220;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[167 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1221);
          reg = x1221;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1222 = arg2[167 * steps + ((cycle - 0) & mask)];
      assert(x1222 != Fp::invalid());
      if (x1222 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1223 = arg2[148 * steps + ((cycle - 0) & mask)];
        assert(x1223 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x1224 = x6 - x1223;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x1224 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1225 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x1225 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1226 = x1225 - x1215;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1227 = x1226 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1228 = Fp(x1227.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1228);
            reg = x1228;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1229 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x1229 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1230 = x1227 - x1229;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1231 = x1230 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1232 = Fp(x1231.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1232);
            reg = x1232;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1233 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x1233 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1234 = x1231 - x1233;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1235 = x1234 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1236 = Fp(x1235.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1236);
            reg = x1236;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1237 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x1237 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1238 = x1235 - x1237;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1239 = x1238 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1239);
          reg = x1239;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x1240 = x1205 * x1217;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x1240 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x1241 = x7 - x1222;
      if (x1241 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1242 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x1242 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x1243 = x1215 - x1242;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x1243 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x1244 = x1210 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1245 = arg2[147 * steps + ((cycle - 0) & mask)];
        assert(x1245 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1246 = arg2[148 * steps + ((cycle - 0) & mask)];
        assert(x1246 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1247 = x1245 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1248 = x1247 + x1246;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1249 = x1248 - x1244;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1250 = x1249 + x1216;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1251 = Fp(x1250.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1251);
            reg = x1251;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1252 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x1252 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1253 = x1250 - x1252;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1254 = x1253 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1255 = Fp(x1254.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1255);
            reg = x1255;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1256 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x1256 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1257 = x1254 - x1256;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1258 = x1257 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1259 = Fp(x1258.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1259);
            reg = x1259;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1260 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x1260 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1261 = x1258 - x1260;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1262 = x1261 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1262);
          reg = x1262;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x1263 = x5 - x1246;
        if (x1263 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1264 = x1211 - x1206;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1264 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1265 = x1212 - x1207;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1265 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1266 = x1213 - x1208;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1266 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1267 = x1214 - x1209;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1267 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x1268 = arg2[148 * steps + ((cycle - 0) & mask)];
      assert(x1268 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x1269 = x6 - x1268;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x1270 = x7 - x1268;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x1271 = x5 - x1268;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x1272 = x1269 * x1271;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x1273 = x1270 * x1269;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x1274 = x1270 * x1271;
      if (x1274 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x1273 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x1272 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1217);
          reg = x1217;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x1275 = arg2[147 * steps + ((cycle - 0) & mask)];
      assert(x1275 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x1276 = arg2[146 * steps + ((cycle - 0) & mask)];
      assert(x1276 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1277 = arg2[156 * steps + ((cycle - 0) & mask)];
      assert(x1277 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1278 = arg2[157 * steps + ((cycle - 0) & mask)];
      assert(x1278 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1279 = arg2[158 * steps + ((cycle - 0) & mask)];
      assert(x1279 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1280 = arg2[159 * steps + ((cycle - 0) & mask)];
      assert(x1280 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1281 = arg2[168 * steps + ((cycle - 0) & mask)];
      assert(x1281 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1282 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x1282 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1283 = x1276 - x1282;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1284 = (x1283 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x1285 = x7 - x1284;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[169 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1285);
          reg = x1285;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1286 = arg2[169 * steps + ((cycle - 0) & mask)];
      assert(x1286 != Fp::invalid());
      if (x1286 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1287 = arg2[155 * steps + ((cycle - 0) & mask)];
        assert(x1287 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x1288 = x6 - x1287;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x1288 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1289 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x1289 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1290 = x1289 - x1276;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1291 = x1290 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1292 = Fp(x1291.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1292);
            reg = x1292;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1293 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x1293 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1294 = x1291 - x1293;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1295 = x1294 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1296 = Fp(x1295.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1296);
            reg = x1296;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1297 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x1297 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1298 = x1295 - x1297;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1299 = x1298 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1300 = Fp(x1299.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1300);
            reg = x1300;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1301 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x1301 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1302 = x1299 - x1301;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1303 = x1302 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1303);
          reg = x1303;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x1304 = x1205 * x1281;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x1304 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x1305 = x7 - x1286;
      if (x1305 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1306 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x1306 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x1307 = x1276 - x1306;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x1307 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x1308 = x1275 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1309 = arg2[154 * steps + ((cycle - 0) & mask)];
        assert(x1309 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1310 = arg2[155 * steps + ((cycle - 0) & mask)];
        assert(x1310 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1311 = x1309 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1312 = x1311 + x1310;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1313 = x1312 - x1308;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1314 = x1313 + x1268;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1315 = Fp(x1314.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1315);
            reg = x1315;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1316 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x1316 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1317 = x1314 - x1316;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1318 = x1317 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1319 = Fp(x1318.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1319);
            reg = x1319;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1320 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x1320 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1321 = x1318 - x1320;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1322 = x1321 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1323 = Fp(x1322.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1323);
            reg = x1323;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1324 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x1324 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1325 = x1322 - x1324;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1326 = x1325 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1326);
          reg = x1326;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x1327 = x5 - x1310;
        if (x1327 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1328 = x1206 - x1277;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1328 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1329 = x1207 - x1278;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1329 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1330 = x1208 - x1279;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1330 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1331 = x1209 - x1280;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1331 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x1332 = arg2[155 * steps + ((cycle - 0) & mask)];
      assert(x1332 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x1333 = x6 - x1332;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x1334 = x7 - x1332;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x1335 = x5 - x1332;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x1336 = x1333 * x1335;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x1337 = x1334 * x1333;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x1338 = x1334 * x1335;
      if (x1338 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x1337 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x1336 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1281);
          reg = x1281;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x1339 = arg2[154 * steps + ((cycle - 0) & mask)];
      assert(x1339 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x1340 = arg2[153 * steps + ((cycle - 0) & mask)];
      assert(x1340 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1341 = arg2[163 * steps + ((cycle - 0) & mask)];
      assert(x1341 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1342 = arg2[164 * steps + ((cycle - 0) & mask)];
      assert(x1342 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1343 = arg2[165 * steps + ((cycle - 0) & mask)];
      assert(x1343 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1344 = arg2[166 * steps + ((cycle - 0) & mask)];
      assert(x1344 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1345 = arg2[170 * steps + ((cycle - 0) & mask)];
      assert(x1345 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1346 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x1346 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1347 = x1340 - x1346;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1348 = (x1347 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x1349 = x7 - x1348;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[171 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1349);
          reg = x1349;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1350 = arg2[171 * steps + ((cycle - 0) & mask)];
      assert(x1350 != Fp::invalid());
      if (x1350 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1351 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x1351 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x1352 = x6 - x1351;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x1352 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1353 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x1353 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1354 = x1353 - x1340;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1355 = x1354 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1356 = Fp(x1355.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1356);
            reg = x1356;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1357 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x1357 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1358 = x1355 - x1357;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1359 = x1358 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1360 = Fp(x1359.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1360);
            reg = x1360;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1361 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x1361 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1362 = x1359 - x1361;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1363 = x1362 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1364 = Fp(x1363.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1364);
            reg = x1364;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1365 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x1365 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1366 = x1363 - x1365;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1367 = x1366 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1367);
          reg = x1367;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x1368 = x1205 * x1345;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x1368 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x1369 = x7 - x1350;
      if (x1369 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1370 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x1370 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x1371 = x1340 - x1370;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x1371 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x1372 = x1339 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1373 = arg2[161 * steps + ((cycle - 0) & mask)];
        assert(x1373 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1374 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x1374 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1375 = x1373 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1376 = x1375 + x1374;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1377 = x1376 - x1372;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1378 = x1377 + x1332;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1379 = Fp(x1378.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1379);
            reg = x1379;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1380 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x1380 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1381 = x1378 - x1380;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1382 = x1381 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1383 = Fp(x1382.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1383);
            reg = x1383;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1384 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x1384 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1385 = x1382 - x1384;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1386 = x1385 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1387 = Fp(x1386.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1387);
            reg = x1387;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1388 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x1388 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1389 = x1386 - x1388;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1390 = x1389 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1390);
          reg = x1390;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x1391 = x5 - x1374;
        if (x1391 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1392 = x1277 - x1341;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1392 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1393 = x1278 - x1342;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1393 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1394 = x1279 - x1343;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1394 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1395 = x1280 - x1344;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1395 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x1396 = arg2[162 * steps + ((cycle - 0) & mask)];
      assert(x1396 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x1397 = x6 - x1396;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x1398 = x7 - x1396;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x1399 = x5 - x1396;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x1400 = x1397 * x1399;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x1401 = x1398 * x1397;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x1402 = x1398 * x1399;
      if (x1402 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x1401 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x1400 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1345);
          reg = x1345;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x1403 = arg2[161 * steps + ((cycle - 0) & mask)];
      assert(x1403 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x1404 = arg2[160 * steps + ((cycle - 0) & mask)];
      assert(x1404 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1405 = arg2[92 * steps + ((cycle - 0) & mask)];
      assert(x1405 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1406 = arg2[93 * steps + ((cycle - 0) & mask)];
      assert(x1406 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1407 = arg2[94 * steps + ((cycle - 0) & mask)];
      assert(x1407 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1408 = arg2[95 * steps + ((cycle - 0) & mask)];
      assert(x1408 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/compute2(ComputeWrap)/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1409 = arg2[172 * steps + ((cycle - 0) & mask)];
      assert(x1409 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1410 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x1410 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1411 = x1404 - x1410;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1412 = (x1411 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x1413 = x7 - x1412;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[96 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1413);
          reg = x1413;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1414 = arg2[96 * steps + ((cycle - 0) & mask)];
      assert(x1414 != Fp::invalid());
      if (x1414 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1415 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x1415 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x1416 = x6 - x1415;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x1416 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1417 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x1417 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1418 = x1417 - x1404;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1419 = x1418 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1420 = Fp(x1419.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1420);
            reg = x1420;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1421 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x1421 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1422 = x1419 - x1421;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1423 = x1422 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1424 = Fp(x1423.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1424);
            reg = x1424;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1425 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x1425 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1426 = x1423 - x1425;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1427 = x1426 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1428 = Fp(x1427.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1428);
            reg = x1428;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1429 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x1429 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1430 = x1427 - x1429;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1431 = x1430 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1431);
          reg = x1431;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x1432 = x1205 * x1409;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x1432 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x1433 = x7 - x1414;
      if (x1433 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1434 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x1434 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x1435 = x1404 - x1434;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x1435 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x1436 = x1403 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1437 = arg2[90 * steps + ((cycle - 0) & mask)];
        assert(x1437 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1438 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x1438 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1439 = x1437 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1440 = x1439 + x1438;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1441 = x1440 - x1436;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1442 = x1441 + x1396;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1443 = Fp(x1442.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1443);
            reg = x1443;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1444 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x1444 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1445 = x1442 - x1444;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1446 = x1445 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1447 = Fp(x1446.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1447);
            reg = x1447;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1448 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x1448 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1449 = x1446 - x1448;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1450 = x1449 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1451 = Fp(x1450.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1451);
            reg = x1451;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1452 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x1452 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1453 = x1450 - x1452;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1454 = x1453 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1454);
          reg = x1454;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x1455 = x5 - x1438;
        if (x1455 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1456 = x1341 - x1405;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1456 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1457 = x1342 - x1406;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1457 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1458 = x1343 - x1407;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1458 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1459 = x1344 - x1408;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1459 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x1460 = arg2[91 * steps + ((cycle - 0) & mask)];
      assert(x1460 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x1461 = x6 - x1460;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x1462 = x7 - x1460;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x1463 = x5 - x1460;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x1464 = x1461 * x1463;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x1465 = x1462 * x1461;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x1466 = x1462 * x1463;
      if (x1466 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x1465 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x1464 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1409);
          reg = x1409;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x1467 = arg2[104 * steps + ((cycle - 0) & mask)];
    assert(x1467 != Fp::invalid());
    if (x1467 != 0) {
      {
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x1468 = extern_outs[0];
        auto x1469 = extern_outs[1];
        auto x1470 = extern_outs[2];
        auto x1471 = extern_outs[3];
        auto x1472 = extern_outs[4];
        auto x1473 = extern_outs[5];
        auto x1474 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1468);
          reg = x1468;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1469);
          reg = x1469;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1470);
          reg = x1470;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1471);
          reg = x1471;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1472);
          reg = x1472;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1473);
          reg = x1473;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1474);
          reg = x1474;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x1475 = extern_outs[0];
        auto x1476 = extern_outs[1];
        auto x1477 = extern_outs[2];
        auto x1478 = extern_outs[3];
        auto x1479 = extern_outs[4];
        auto x1480 = extern_outs[5];
        auto x1481 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1475);
          reg = x1475;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[161 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1476);
          reg = x1476;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[162 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1477);
          reg = x1477;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[163 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1478);
          reg = x1478;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[164 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1479);
          reg = x1479;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[165 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1480);
          reg = x1480;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[166 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1481);
          reg = x1481;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x1482 = extern_outs[0];
        auto x1483 = extern_outs[1];
        auto x1484 = extern_outs[2];
        auto x1485 = extern_outs[3];
        auto x1486 = extern_outs[4];
        auto x1487 = extern_outs[5];
        auto x1488 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[167 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1482);
          reg = x1482;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1483);
          reg = x1483;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[169 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1484);
          reg = x1484;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1485);
          reg = x1485;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[171 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1486);
          reg = x1486;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1487);
          reg = x1487;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[173 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1488);
          reg = x1488;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x1489 = extern_outs[0];
        auto x1490 = extern_outs[1];
        auto x1491 = extern_outs[2];
        auto x1492 = extern_outs[3];
        auto x1493 = extern_outs[4];
        auto x1494 = extern_outs[5];
        auto x1495 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[174 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1489);
          reg = x1489;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[175 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1490);
          reg = x1490;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[176 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1491);
          reg = x1491;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[177 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1492);
          reg = x1492;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[178 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1493);
          reg = x1493;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[179 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1494);
          reg = x1494;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[180 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1495);
          reg = x1495;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x1496 = extern_outs[0];
        auto x1497 = extern_outs[1];
        auto x1498 = extern_outs[2];
        auto x1499 = extern_outs[3];
        auto x1500 = extern_outs[4];
        auto x1501 = extern_outs[5];
        auto x1502 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[89 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1496);
          reg = x1496;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[90 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1497);
          reg = x1497;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[91 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1498);
          reg = x1498;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[92 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1499);
          reg = x1499;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[93 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1500);
          reg = x1500;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[94 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1501);
          reg = x1501;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[95 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1502);
          reg = x1502;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/global(Global)/sys_exit_code(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1503 = arg1[104];
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1504 = arg2[156 * steps + ((cycle - 0) & mask)];
      assert(x1504 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1505 = arg2[157 * steps + ((cycle - 0) & mask)];
      assert(x1505 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1506 = arg2[158 * steps + ((cycle - 0) & mask)];
      assert(x1506 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1507 = arg2[159 * steps + ((cycle - 0) & mask)];
      assert(x1507 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x1508 = arg2[90 * steps + ((cycle - 1) & mask)];
      assert(x1508 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1509 = arg2[92 * steps + ((cycle - 1) & mask)];
      assert(x1509 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1510 = arg2[93 * steps + ((cycle - 1) & mask)];
      assert(x1510 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1511 = arg2[94 * steps + ((cycle - 1) & mask)];
      assert(x1511 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1512 = arg2[95 * steps + ((cycle - 1) & mask)];
      assert(x1512 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x1513 = arg2[89 * steps + ((cycle - 1) & mask)];
      assert(x1513 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("zirgen/components/ram.cpp":67:42))
      auto x1514 = arg2[91 * steps + ((cycle - 1) & mask)];
      assert(x1514 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1515 = arg2[97 * steps + ((cycle - 1) & mask)];
      assert(x1515 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1516 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x1516 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1517 = x1513 - x1516;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1518 = (x1517 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x1519 = x7 - x1518;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[181 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1519);
          reg = x1519;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1520 = arg2[181 * steps + ((cycle - 0) & mask)];
      assert(x1520 != Fp::invalid());
      if (x1520 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1521 = arg2[155 * steps + ((cycle - 0) & mask)];
        assert(x1521 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x1522 = x6 - x1521;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x1522 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1523 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x1523 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1524 = x1523 - x1513;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1525 = x1524 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1526 = Fp(x1525.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1526);
            reg = x1526;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1527 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x1527 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1528 = x1525 - x1527;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1529 = x1528 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1530 = Fp(x1529.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1530);
            reg = x1530;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1531 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x1531 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1532 = x1529 - x1531;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1533 = x1532 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1534 = Fp(x1533.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1534);
            reg = x1534;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1535 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x1535 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1536 = x1533 - x1535;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1537 = x1536 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1537);
          reg = x1537;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x1538 = x1503 * x1515;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x1538 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x1539 = x7 - x1520;
      if (x1539 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1540 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x1540 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x1541 = x1513 - x1540;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x1541 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x1542 = x1508 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1543 = arg2[154 * steps + ((cycle - 0) & mask)];
        assert(x1543 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1544 = arg2[155 * steps + ((cycle - 0) & mask)];
        assert(x1544 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1545 = x1543 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1546 = x1545 + x1544;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1547 = x1546 - x1542;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1548 = x1547 + x1514;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1549 = Fp(x1548.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1549);
            reg = x1549;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1550 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x1550 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1551 = x1548 - x1550;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1552 = x1551 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1553 = Fp(x1552.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1553);
            reg = x1553;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1554 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x1554 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1555 = x1552 - x1554;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1556 = x1555 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1557 = Fp(x1556.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1557);
            reg = x1557;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1558 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x1558 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1559 = x1556 - x1558;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1560 = x1559 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1560);
          reg = x1560;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x1561 = x5 - x1544;
        if (x1561 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1562 = x1509 - x1504;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1562 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1563 = x1510 - x1505;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1563 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1564 = x1511 - x1506;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1564 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1565 = x1512 - x1507;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1565 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x1566 = arg2[155 * steps + ((cycle - 0) & mask)];
      assert(x1566 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x1567 = x6 - x1566;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x1568 = x7 - x1566;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x1569 = x5 - x1566;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x1570 = x1567 * x1569;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x1571 = x1568 * x1567;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x1572 = x1568 * x1569;
      if (x1572 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[182 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x1571 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[182 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x1570 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[182 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1515);
          reg = x1515;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x1573 = arg2[154 * steps + ((cycle - 0) & mask)];
      assert(x1573 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x1574 = arg2[153 * steps + ((cycle - 0) & mask)];
      assert(x1574 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1575 = arg2[163 * steps + ((cycle - 0) & mask)];
      assert(x1575 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1576 = arg2[164 * steps + ((cycle - 0) & mask)];
      assert(x1576 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1577 = arg2[165 * steps + ((cycle - 0) & mask)];
      assert(x1577 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1578 = arg2[166 * steps + ((cycle - 0) & mask)];
      assert(x1578 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1579 = arg2[182 * steps + ((cycle - 0) & mask)];
      assert(x1579 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1580 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x1580 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1581 = x1574 - x1580;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1582 = (x1581 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x1583 = x7 - x1582;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[183 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1583);
          reg = x1583;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1584 = arg2[183 * steps + ((cycle - 0) & mask)];
      assert(x1584 != Fp::invalid());
      if (x1584 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1585 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x1585 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x1586 = x6 - x1585;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x1586 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1587 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x1587 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1588 = x1587 - x1574;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1589 = x1588 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1590 = Fp(x1589.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1590);
            reg = x1590;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1591 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x1591 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1592 = x1589 - x1591;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1593 = x1592 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1594 = Fp(x1593.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1594);
            reg = x1594;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1595 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x1595 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1596 = x1593 - x1595;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1597 = x1596 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1598 = Fp(x1597.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1598);
            reg = x1598;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1599 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x1599 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1600 = x1597 - x1599;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1601 = x1600 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1601);
          reg = x1601;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x1602 = x1503 * x1579;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x1602 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x1603 = x7 - x1584;
      if (x1603 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1604 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x1604 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x1605 = x1574 - x1604;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x1605 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x1606 = x1573 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1607 = arg2[161 * steps + ((cycle - 0) & mask)];
        assert(x1607 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1608 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x1608 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1609 = x1607 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1610 = x1609 + x1608;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1611 = x1610 - x1606;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1612 = x1611 + x1566;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1613 = Fp(x1612.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1613);
            reg = x1613;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1614 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x1614 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1615 = x1612 - x1614;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1616 = x1615 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1617 = Fp(x1616.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1617);
            reg = x1617;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1618 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x1618 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1619 = x1616 - x1618;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1620 = x1619 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1621 = Fp(x1620.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1621);
            reg = x1621;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1622 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x1622 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1623 = x1620 - x1622;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1624 = x1623 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1624);
          reg = x1624;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x1625 = x5 - x1608;
        if (x1625 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1626 = x1504 - x1575;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1626 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1627 = x1505 - x1576;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1627 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1628 = x1506 - x1577;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1628 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1629 = x1507 - x1578;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1629 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x1630 = arg2[162 * steps + ((cycle - 0) & mask)];
      assert(x1630 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x1631 = x6 - x1630;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x1632 = x7 - x1630;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x1633 = x5 - x1630;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x1634 = x1631 * x1633;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x1635 = x1632 * x1631;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x1636 = x1632 * x1633;
      if (x1636 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[184 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x1635 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[184 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x1634 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[184 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1579);
          reg = x1579;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x1637 = arg2[161 * steps + ((cycle - 0) & mask)];
      assert(x1637 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x1638 = arg2[160 * steps + ((cycle - 0) & mask)];
      assert(x1638 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1639 = arg2[170 * steps + ((cycle - 0) & mask)];
      assert(x1639 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1640 = arg2[171 * steps + ((cycle - 0) & mask)];
      assert(x1640 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1641 = arg2[172 * steps + ((cycle - 0) & mask)];
      assert(x1641 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1642 = arg2[173 * steps + ((cycle - 0) & mask)];
      assert(x1642 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1643 = arg2[184 * steps + ((cycle - 0) & mask)];
      assert(x1643 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1644 = arg2[167 * steps + ((cycle - 0) & mask)];
        assert(x1644 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1645 = x1638 - x1644;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1646 = (x1645 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x1647 = x7 - x1646;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[185 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1647);
          reg = x1647;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1648 = arg2[185 * steps + ((cycle - 0) & mask)];
      assert(x1648 != Fp::invalid());
      if (x1648 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1649 = arg2[169 * steps + ((cycle - 0) & mask)];
        assert(x1649 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x1650 = x6 - x1649;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x1650 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1651 = arg2[167 * steps + ((cycle - 0) & mask)];
        assert(x1651 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1652 = x1651 - x1638;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1653 = x1652 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1654 = Fp(x1653.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1654);
            reg = x1654;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1655 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x1655 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1656 = x1653 - x1655;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1657 = x1656 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1658 = Fp(x1657.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1658);
            reg = x1658;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1659 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x1659 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1660 = x1657 - x1659;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1661 = x1660 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1662 = Fp(x1661.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1662);
            reg = x1662;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1663 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x1663 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1664 = x1661 - x1663;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1665 = x1664 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1665);
          reg = x1665;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x1666 = x1503 * x1643;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x1666 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x1667 = x7 - x1648;
      if (x1667 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1668 = arg2[167 * steps + ((cycle - 0) & mask)];
        assert(x1668 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x1669 = x1638 - x1668;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x1669 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x1670 = x1637 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1671 = arg2[168 * steps + ((cycle - 0) & mask)];
        assert(x1671 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1672 = arg2[169 * steps + ((cycle - 0) & mask)];
        assert(x1672 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1673 = x1671 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1674 = x1673 + x1672;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1675 = x1674 - x1670;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1676 = x1675 + x1630;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1677 = Fp(x1676.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1677);
            reg = x1677;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1678 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x1678 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1679 = x1676 - x1678;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1680 = x1679 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1681 = Fp(x1680.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1681);
            reg = x1681;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1682 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x1682 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1683 = x1680 - x1682;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1684 = x1683 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1685 = Fp(x1684.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1685);
            reg = x1685;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1686 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x1686 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1687 = x1684 - x1686;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1688 = x1687 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1688);
          reg = x1688;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x1689 = x5 - x1672;
        if (x1689 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1690 = x1575 - x1639;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1690 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1691 = x1576 - x1640;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1691 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1692 = x1577 - x1641;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1692 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1693 = x1578 - x1642;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1693 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x1694 = arg2[169 * steps + ((cycle - 0) & mask)];
      assert(x1694 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x1695 = x6 - x1694;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x1696 = x7 - x1694;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x1697 = x5 - x1694;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x1698 = x1695 * x1697;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x1699 = x1696 * x1695;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x1700 = x1696 * x1697;
      if (x1700 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[186 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x1699 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[186 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x1698 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[186 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1643);
          reg = x1643;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x1701 = arg2[168 * steps + ((cycle - 0) & mask)];
      assert(x1701 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x1702 = arg2[167 * steps + ((cycle - 0) & mask)];
      assert(x1702 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1703 = arg2[177 * steps + ((cycle - 0) & mask)];
      assert(x1703 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1704 = arg2[178 * steps + ((cycle - 0) & mask)];
      assert(x1704 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1705 = arg2[179 * steps + ((cycle - 0) & mask)];
      assert(x1705 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1706 = arg2[180 * steps + ((cycle - 0) & mask)];
      assert(x1706 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1707 = arg2[186 * steps + ((cycle - 0) & mask)];
      assert(x1707 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1708 = arg2[174 * steps + ((cycle - 0) & mask)];
        assert(x1708 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1709 = x1702 - x1708;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1710 = (x1709 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x1711 = x7 - x1710;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[187 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1711);
          reg = x1711;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1712 = arg2[187 * steps + ((cycle - 0) & mask)];
      assert(x1712 != Fp::invalid());
      if (x1712 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1713 = arg2[176 * steps + ((cycle - 0) & mask)];
        assert(x1713 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x1714 = x6 - x1713;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x1714 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1715 = arg2[174 * steps + ((cycle - 0) & mask)];
        assert(x1715 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1716 = x1715 - x1702;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1717 = x1716 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1718 = Fp(x1717.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1718);
            reg = x1718;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1719 = arg2[18 * steps + ((cycle - 0) & mask)];
        assert(x1719 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1720 = x1717 - x1719;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1721 = x1720 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1722 = Fp(x1721.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1722);
            reg = x1722;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1723 = arg2[19 * steps + ((cycle - 0) & mask)];
        assert(x1723 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1724 = x1721 - x1723;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1725 = x1724 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1726 = Fp(x1725.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1726);
            reg = x1726;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1727 = arg2[20 * steps + ((cycle - 0) & mask)];
        assert(x1727 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1728 = x1725 - x1727;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1729 = x1728 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1729);
          reg = x1729;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x1730 = x1503 * x1707;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x1730 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x1731 = x7 - x1712;
      if (x1731 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1732 = arg2[174 * steps + ((cycle - 0) & mask)];
        assert(x1732 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x1733 = x1702 - x1732;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x1733 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x1734 = x1701 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1735 = arg2[175 * steps + ((cycle - 0) & mask)];
        assert(x1735 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1736 = arg2[176 * steps + ((cycle - 0) & mask)];
        assert(x1736 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1737 = x1735 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1738 = x1737 + x1736;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1739 = x1738 - x1734;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1740 = x1739 + x1694;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1741 = Fp(x1740.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1741);
            reg = x1741;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1742 = arg2[18 * steps + ((cycle - 0) & mask)];
        assert(x1742 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1743 = x1740 - x1742;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1744 = x1743 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1745 = Fp(x1744.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1745);
            reg = x1745;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1746 = arg2[19 * steps + ((cycle - 0) & mask)];
        assert(x1746 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1747 = x1744 - x1746;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1748 = x1747 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1749 = Fp(x1748.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1749);
            reg = x1749;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1750 = arg2[20 * steps + ((cycle - 0) & mask)];
        assert(x1750 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1751 = x1748 - x1750;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1752 = x1751 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1752);
          reg = x1752;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x1753 = x5 - x1736;
        if (x1753 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1754 = x1639 - x1703;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1754 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1755 = x1640 - x1704;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1755 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1756 = x1641 - x1705;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1756 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1757 = x1642 - x1706;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1757 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x1758 = arg2[176 * steps + ((cycle - 0) & mask)];
      assert(x1758 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x1759 = x6 - x1758;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x1760 = x7 - x1758;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x1761 = x5 - x1758;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x1762 = x1759 * x1761;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x1763 = x1760 * x1759;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x1764 = x1760 * x1761;
      if (x1764 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[188 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x1763 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[188 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x1762 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[188 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1707);
          reg = x1707;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x1765 = arg2[175 * steps + ((cycle - 0) & mask)];
      assert(x1765 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x1766 = arg2[174 * steps + ((cycle - 0) & mask)];
      assert(x1766 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1767 = arg2[92 * steps + ((cycle - 0) & mask)];
      assert(x1767 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1768 = arg2[93 * steps + ((cycle - 0) & mask)];
      assert(x1768 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1769 = arg2[94 * steps + ((cycle - 0) & mask)];
      assert(x1769 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1770 = arg2[95 * steps + ((cycle - 0) & mask)];
      assert(x1770 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/mem_io(MemIOCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1771 = arg2[188 * steps + ((cycle - 0) & mask)];
      assert(x1771 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1772 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x1772 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1773 = x1766 - x1772;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1774 = (x1773 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x1775 = x7 - x1774;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[96 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1775);
          reg = x1775;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1776 = arg2[96 * steps + ((cycle - 0) & mask)];
      assert(x1776 != Fp::invalid());
      if (x1776 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1777 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x1777 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x1778 = x6 - x1777;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x1778 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1779 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x1779 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1780 = x1779 - x1766;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1781 = x1780 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1782 = Fp(x1781.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1782);
            reg = x1782;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1783 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x1783 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1784 = x1781 - x1783;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1785 = x1784 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1786 = Fp(x1785.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1786);
            reg = x1786;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1787 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x1787 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1788 = x1785 - x1787;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1789 = x1788 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1790 = Fp(x1789.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1790);
            reg = x1790;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1791 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x1791 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1792 = x1789 - x1791;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1793 = x1792 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1793);
          reg = x1793;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x1794 = x1503 * x1771;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x1794 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x1795 = x7 - x1776;
      if (x1795 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1796 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x1796 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x1797 = x1766 - x1796;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x1797 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x1798 = x1765 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1799 = arg2[90 * steps + ((cycle - 0) & mask)];
        assert(x1799 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1800 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x1800 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1801 = x1799 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1802 = x1801 + x1800;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1803 = x1802 - x1798;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1804 = x1803 + x1758;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1805 = Fp(x1804.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1805);
            reg = x1805;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1806 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x1806 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1807 = x1804 - x1806;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1808 = x1807 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1809 = Fp(x1808.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1809);
            reg = x1809;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1810 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x1810 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1811 = x1808 - x1810;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1812 = x1811 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1813 = Fp(x1812.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1813);
            reg = x1813;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1814 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x1814 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1815 = x1812 - x1814;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1816 = x1815 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1816);
          reg = x1816;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x1817 = x5 - x1800;
        if (x1817 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1818 = x1703 - x1767;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1818 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1819 = x1704 - x1768;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1819 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1820 = x1705 - x1769;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1820 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1821 = x1706 - x1770;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1821 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x1822 = arg2[91 * steps + ((cycle - 0) & mask)];
      assert(x1822 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x1823 = x6 - x1822;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x1824 = x7 - x1822;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x1825 = x5 - x1822;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x1826 = x1823 * x1825;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x1827 = x1824 * x1823;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x1828 = x1824 * x1825;
      if (x1828 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x1827 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x1826 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1771);
          reg = x1771;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x1829 = arg2[105 * steps + ((cycle - 0) & mask)];
    assert(x1829 != Fp::invalid());
    if (x1829 != 0) {
      {
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x1830 = extern_outs[0];
        auto x1831 = extern_outs[1];
        auto x1832 = extern_outs[2];
        auto x1833 = extern_outs[3];
        auto x1834 = extern_outs[4];
        auto x1835 = extern_outs[5];
        auto x1836 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1830);
          reg = x1830;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1831);
          reg = x1831;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1832);
          reg = x1832;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1833);
          reg = x1833;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1834);
          reg = x1834;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1835);
          reg = x1835;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1836);
          reg = x1836;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x1837 = extern_outs[0];
        auto x1838 = extern_outs[1];
        auto x1839 = extern_outs[2];
        auto x1840 = extern_outs[3];
        auto x1841 = extern_outs[4];
        auto x1842 = extern_outs[5];
        auto x1843 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1837);
          reg = x1837;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1838);
          reg = x1838;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1839);
          reg = x1839;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1840);
          reg = x1840;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1841);
          reg = x1841;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1842);
          reg = x1842;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1843);
          reg = x1843;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x1844 = extern_outs[0];
        auto x1845 = extern_outs[1];
        auto x1846 = extern_outs[2];
        auto x1847 = extern_outs[3];
        auto x1848 = extern_outs[4];
        auto x1849 = extern_outs[5];
        auto x1850 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1844);
          reg = x1844;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[161 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1845);
          reg = x1845;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[162 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1846);
          reg = x1846;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[163 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1847);
          reg = x1847;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[164 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1848);
          reg = x1848;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[165 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1849);
          reg = x1849;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[166 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1850);
          reg = x1850;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x1851 = extern_outs[0];
        auto x1852 = extern_outs[1];
        auto x1853 = extern_outs[2];
        auto x1854 = extern_outs[3];
        auto x1855 = extern_outs[4];
        auto x1856 = extern_outs[5];
        auto x1857 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[89 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1851);
          reg = x1851;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[90 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1852);
          reg = x1852;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[91 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1853);
          reg = x1853;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[92 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1854);
          reg = x1854;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[93 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1855);
          reg = x1855;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[94 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1856);
          reg = x1856;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[95 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1857);
          reg = x1857;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/global(Global)/sys_exit_code(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1858 = arg1[104];
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1859 = arg2[149 * steps + ((cycle - 0) & mask)];
      assert(x1859 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1860 = arg2[150 * steps + ((cycle - 0) & mask)];
      assert(x1860 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1861 = arg2[151 * steps + ((cycle - 0) & mask)];
      assert(x1861 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1862 = arg2[152 * steps + ((cycle - 0) & mask)];
      assert(x1862 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x1863 = arg2[90 * steps + ((cycle - 1) & mask)];
      assert(x1863 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1864 = arg2[92 * steps + ((cycle - 1) & mask)];
      assert(x1864 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1865 = arg2[93 * steps + ((cycle - 1) & mask)];
      assert(x1865 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1866 = arg2[94 * steps + ((cycle - 1) & mask)];
      assert(x1866 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1867 = arg2[95 * steps + ((cycle - 1) & mask)];
      assert(x1867 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x1868 = arg2[89 * steps + ((cycle - 1) & mask)];
      assert(x1868 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("zirgen/components/ram.cpp":67:42))
      auto x1869 = arg2[91 * steps + ((cycle - 1) & mask)];
      assert(x1869 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1870 = arg2[97 * steps + ((cycle - 1) & mask)];
      assert(x1870 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1871 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x1871 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1872 = x1868 - x1871;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1873 = (x1872 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x1874 = x7 - x1873;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[167 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1874);
          reg = x1874;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1875 = arg2[167 * steps + ((cycle - 0) & mask)];
      assert(x1875 != Fp::invalid());
      if (x1875 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1876 = arg2[148 * steps + ((cycle - 0) & mask)];
        assert(x1876 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x1877 = x6 - x1876;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x1877 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1878 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x1878 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1879 = x1878 - x1868;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1880 = x1879 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1881 = Fp(x1880.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1881);
            reg = x1881;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1882 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x1882 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1883 = x1880 - x1882;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1884 = x1883 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1885 = Fp(x1884.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1885);
            reg = x1885;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1886 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x1886 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1887 = x1884 - x1886;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1888 = x1887 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1889 = Fp(x1888.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1889);
            reg = x1889;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1890 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x1890 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1891 = x1888 - x1890;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1892 = x1891 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1892);
          reg = x1892;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x1893 = x1858 * x1870;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x1893 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x1894 = x7 - x1875;
      if (x1894 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1895 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x1895 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x1896 = x1868 - x1895;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x1896 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x1897 = x1863 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1898 = arg2[147 * steps + ((cycle - 0) & mask)];
        assert(x1898 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1899 = arg2[148 * steps + ((cycle - 0) & mask)];
        assert(x1899 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1900 = x1898 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1901 = x1900 + x1899;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1902 = x1901 - x1897;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1903 = x1902 + x1869;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1904 = Fp(x1903.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1904);
            reg = x1904;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1905 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x1905 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1906 = x1903 - x1905;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1907 = x1906 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1908 = Fp(x1907.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1908);
            reg = x1908;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1909 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x1909 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1910 = x1907 - x1909;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1911 = x1910 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1912 = Fp(x1911.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1912);
            reg = x1912;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1913 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x1913 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1914 = x1911 - x1913;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1915 = x1914 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1915);
          reg = x1915;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x1916 = x5 - x1899;
        if (x1916 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1917 = x1864 - x1859;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1917 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1918 = x1865 - x1860;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1918 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1919 = x1866 - x1861;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1919 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1920 = x1867 - x1862;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1920 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x1921 = arg2[148 * steps + ((cycle - 0) & mask)];
      assert(x1921 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x1922 = x6 - x1921;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x1923 = x7 - x1921;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x1924 = x5 - x1921;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x1925 = x1922 * x1924;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x1926 = x1923 * x1922;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x1927 = x1923 * x1924;
      if (x1927 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x1926 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x1925 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1870);
          reg = x1870;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x1928 = arg2[147 * steps + ((cycle - 0) & mask)];
      assert(x1928 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x1929 = arg2[146 * steps + ((cycle - 0) & mask)];
      assert(x1929 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1930 = arg2[156 * steps + ((cycle - 0) & mask)];
      assert(x1930 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1931 = arg2[157 * steps + ((cycle - 0) & mask)];
      assert(x1931 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1932 = arg2[158 * steps + ((cycle - 0) & mask)];
      assert(x1932 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1933 = arg2[159 * steps + ((cycle - 0) & mask)];
      assert(x1933 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1934 = arg2[168 * steps + ((cycle - 0) & mask)];
      assert(x1934 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1935 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x1935 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1936 = x1929 - x1935;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x1937 = (x1936 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x1938 = x7 - x1937;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[169 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1938);
          reg = x1938;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1939 = arg2[169 * steps + ((cycle - 0) & mask)];
      assert(x1939 != Fp::invalid());
      if (x1939 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1940 = arg2[155 * steps + ((cycle - 0) & mask)];
        assert(x1940 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x1941 = x6 - x1940;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x1941 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1942 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x1942 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1943 = x1942 - x1929;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x1944 = x1943 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1945 = Fp(x1944.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1945);
            reg = x1945;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1946 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x1946 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1947 = x1944 - x1946;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1948 = x1947 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1949 = Fp(x1948.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1949);
            reg = x1949;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1950 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x1950 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1951 = x1948 - x1950;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1952 = x1951 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1953 = Fp(x1952.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1953);
            reg = x1953;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1954 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x1954 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1955 = x1952 - x1954;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1956 = x1955 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1956);
          reg = x1956;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x1957 = x1858 * x1934;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x1957 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x1958 = x7 - x1939;
      if (x1958 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1959 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x1959 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x1960 = x1929 - x1959;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x1960 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x1961 = x1928 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1962 = arg2[154 * steps + ((cycle - 0) & mask)];
        assert(x1962 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1963 = arg2[155 * steps + ((cycle - 0) & mask)];
        assert(x1963 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1964 = x1962 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1965 = x1964 + x1963;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1966 = x1965 - x1961;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x1967 = x1966 + x1921;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1968 = Fp(x1967.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1968);
            reg = x1968;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1969 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x1969 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1970 = x1967 - x1969;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1971 = x1970 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1972 = Fp(x1971.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1972);
            reg = x1972;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1973 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x1973 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1974 = x1971 - x1973;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1975 = x1974 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x1976 = Fp(x1975.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1976);
            reg = x1976;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x1977 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x1977 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x1978 = x1975 - x1977;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x1979 = x1978 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1979);
          reg = x1979;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x1980 = x5 - x1963;
        if (x1980 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1981 = x1859 - x1930;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1981 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1982 = x1860 - x1931;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1982 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1983 = x1861 - x1932;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1983 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x1984 = x1862 - x1933;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x1984 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x1985 = arg2[155 * steps + ((cycle - 0) & mask)];
      assert(x1985 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x1986 = x6 - x1985;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x1987 = x7 - x1985;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x1988 = x5 - x1985;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x1989 = x1986 * x1988;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x1990 = x1987 * x1986;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x1991 = x1987 * x1988;
      if (x1991 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x1990 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x1989 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1934);
          reg = x1934;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x1992 = arg2[154 * steps + ((cycle - 0) & mask)];
      assert(x1992 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x1993 = arg2[153 * steps + ((cycle - 0) & mask)];
      assert(x1993 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1994 = arg2[163 * steps + ((cycle - 0) & mask)];
      assert(x1994 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1995 = arg2[164 * steps + ((cycle - 0) & mask)];
      assert(x1995 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1996 = arg2[165 * steps + ((cycle - 0) & mask)];
      assert(x1996 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1997 = arg2[166 * steps + ((cycle - 0) & mask)];
      assert(x1997 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x1998 = arg2[170 * steps + ((cycle - 0) & mask)];
      assert(x1998 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x1999 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x1999 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2000 = x1993 - x1999;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2001 = (x2000 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x2002 = x7 - x2001;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[171 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2002);
          reg = x2002;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2003 = arg2[171 * steps + ((cycle - 0) & mask)];
      assert(x2003 != Fp::invalid());
      if (x2003 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2004 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x2004 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x2005 = x6 - x2004;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x2005 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2006 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x2006 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2007 = x2006 - x1993;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2008 = x2007 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2009 = Fp(x2008.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2009);
            reg = x2009;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2010 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x2010 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2011 = x2008 - x2010;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2012 = x2011 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2013 = Fp(x2012.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2013);
            reg = x2013;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2014 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x2014 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2015 = x2012 - x2014;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2016 = x2015 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2017 = Fp(x2016.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2017);
            reg = x2017;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2018 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x2018 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2019 = x2016 - x2018;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2020 = x2019 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2020);
          reg = x2020;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x2021 = x1858 * x1998;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x2021 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x2022 = x7 - x2003;
      if (x2022 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2023 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x2023 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x2024 = x1993 - x2023;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x2024 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x2025 = x1992 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2026 = arg2[161 * steps + ((cycle - 0) & mask)];
        assert(x2026 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2027 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x2027 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2028 = x2026 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2029 = x2028 + x2027;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2030 = x2029 - x2025;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2031 = x2030 + x1985;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2032 = Fp(x2031.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2032);
            reg = x2032;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2033 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x2033 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2034 = x2031 - x2033;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2035 = x2034 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2036 = Fp(x2035.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2036);
            reg = x2036;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2037 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x2037 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2038 = x2035 - x2037;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2039 = x2038 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2040 = Fp(x2039.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2040);
            reg = x2040;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2041 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x2041 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2042 = x2039 - x2041;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2043 = x2042 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2043);
          reg = x2043;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x2044 = x5 - x2027;
        if (x2044 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2045 = x1930 - x1994;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2045 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2046 = x1931 - x1995;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2046 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2047 = x1932 - x1996;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2047 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2048 = x1933 - x1997;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2048 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x2049 = arg2[162 * steps + ((cycle - 0) & mask)];
      assert(x2049 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x2050 = x6 - x2049;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x2051 = x7 - x2049;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x2052 = x5 - x2049;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x2053 = x2050 * x2052;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x2054 = x2051 * x2050;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x2055 = x2051 * x2052;
      if (x2055 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x2054 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x2053 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1998);
          reg = x1998;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x2056 = arg2[161 * steps + ((cycle - 0) & mask)];
      assert(x2056 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x2057 = arg2[160 * steps + ((cycle - 0) & mask)];
      assert(x2057 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2058 = arg2[92 * steps + ((cycle - 0) & mask)];
      assert(x2058 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2059 = arg2[93 * steps + ((cycle - 0) & mask)];
      assert(x2059 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2060 = arg2[94 * steps + ((cycle - 0) & mask)];
      assert(x2060 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2061 = arg2[95 * steps + ((cycle - 0) & mask)];
      assert(x2061 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/multiply(MultiplyCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2062 = arg2[172 * steps + ((cycle - 0) & mask)];
      assert(x2062 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2063 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x2063 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2064 = x2057 - x2063;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2065 = (x2064 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x2066 = x7 - x2065;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[96 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2066);
          reg = x2066;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2067 = arg2[96 * steps + ((cycle - 0) & mask)];
      assert(x2067 != Fp::invalid());
      if (x2067 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2068 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x2068 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x2069 = x6 - x2068;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x2069 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2070 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x2070 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2071 = x2070 - x2057;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2072 = x2071 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2073 = Fp(x2072.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2073);
            reg = x2073;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2074 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x2074 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2075 = x2072 - x2074;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2076 = x2075 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2077 = Fp(x2076.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2077);
            reg = x2077;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2078 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x2078 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2079 = x2076 - x2078;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2080 = x2079 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2081 = Fp(x2080.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2081);
            reg = x2081;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2082 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x2082 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2083 = x2080 - x2082;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2084 = x2083 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2084);
          reg = x2084;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x2085 = x1858 * x2062;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x2085 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x2086 = x7 - x2067;
      if (x2086 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2087 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x2087 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x2088 = x2057 - x2087;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x2088 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x2089 = x2056 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2090 = arg2[90 * steps + ((cycle - 0) & mask)];
        assert(x2090 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2091 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x2091 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2092 = x2090 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2093 = x2092 + x2091;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2094 = x2093 - x2089;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2095 = x2094 + x2049;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2096 = Fp(x2095.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2096);
            reg = x2096;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2097 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x2097 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2098 = x2095 - x2097;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2099 = x2098 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2100 = Fp(x2099.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2100);
            reg = x2100;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2101 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x2101 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2102 = x2099 - x2101;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2103 = x2102 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2104 = Fp(x2103.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2104);
            reg = x2104;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2105 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x2105 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2106 = x2103 - x2105;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2107 = x2106 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2107);
          reg = x2107;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x2108 = x5 - x2091;
        if (x2108 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2109 = x1994 - x2058;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2109 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2110 = x1995 - x2059;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2110 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2111 = x1996 - x2060;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2111 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2112 = x1997 - x2061;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2112 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x2113 = arg2[91 * steps + ((cycle - 0) & mask)];
      assert(x2113 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x2114 = x6 - x2113;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x2115 = x7 - x2113;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x2116 = x5 - x2113;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x2117 = x2114 * x2116;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x2118 = x2115 * x2114;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x2119 = x2115 * x2116;
      if (x2119 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x2118 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x2117 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2062);
          reg = x2062;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x2120 = arg2[106 * steps + ((cycle - 0) & mask)];
    assert(x2120 != Fp::invalid());
    if (x2120 != 0) {
      {
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x2121 = extern_outs[0];
        auto x2122 = extern_outs[1];
        auto x2123 = extern_outs[2];
        auto x2124 = extern_outs[3];
        auto x2125 = extern_outs[4];
        auto x2126 = extern_outs[5];
        auto x2127 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2121);
          reg = x2121;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2122);
          reg = x2122;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2123);
          reg = x2123;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2124);
          reg = x2124;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2125);
          reg = x2125;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2126);
          reg = x2126;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2127);
          reg = x2127;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x2128 = extern_outs[0];
        auto x2129 = extern_outs[1];
        auto x2130 = extern_outs[2];
        auto x2131 = extern_outs[3];
        auto x2132 = extern_outs[4];
        auto x2133 = extern_outs[5];
        auto x2134 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2128);
          reg = x2128;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2129);
          reg = x2129;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2130);
          reg = x2130;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2131);
          reg = x2131;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2132);
          reg = x2132;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2133);
          reg = x2133;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2134);
          reg = x2134;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x2135 = extern_outs[0];
        auto x2136 = extern_outs[1];
        auto x2137 = extern_outs[2];
        auto x2138 = extern_outs[3];
        auto x2139 = extern_outs[4];
        auto x2140 = extern_outs[5];
        auto x2141 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2135);
          reg = x2135;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[161 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2136);
          reg = x2136;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[162 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2137);
          reg = x2137;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[163 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2138);
          reg = x2138;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[164 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2139);
          reg = x2139;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[165 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2140);
          reg = x2140;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[166 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2141);
          reg = x2141;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x2142 = extern_outs[0];
        auto x2143 = extern_outs[1];
        auto x2144 = extern_outs[2];
        auto x2145 = extern_outs[3];
        auto x2146 = extern_outs[4];
        auto x2147 = extern_outs[5];
        auto x2148 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[89 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2142);
          reg = x2142;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[90 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2143);
          reg = x2143;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[91 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2144);
          reg = x2144;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[92 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2145);
          reg = x2145;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[93 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2146);
          reg = x2146;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[94 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2147);
          reg = x2147;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[95 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2148);
          reg = x2148;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/global(Global)/sys_exit_code(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2149 = arg1[104];
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2150 = arg2[149 * steps + ((cycle - 0) & mask)];
      assert(x2150 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2151 = arg2[150 * steps + ((cycle - 0) & mask)];
      assert(x2151 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2152 = arg2[151 * steps + ((cycle - 0) & mask)];
      assert(x2152 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2153 = arg2[152 * steps + ((cycle - 0) & mask)];
      assert(x2153 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x2154 = arg2[90 * steps + ((cycle - 1) & mask)];
      assert(x2154 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2155 = arg2[92 * steps + ((cycle - 1) & mask)];
      assert(x2155 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2156 = arg2[93 * steps + ((cycle - 1) & mask)];
      assert(x2156 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2157 = arg2[94 * steps + ((cycle - 1) & mask)];
      assert(x2157 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2158 = arg2[95 * steps + ((cycle - 1) & mask)];
      assert(x2158 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x2159 = arg2[89 * steps + ((cycle - 1) & mask)];
      assert(x2159 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("zirgen/components/ram.cpp":67:42))
      auto x2160 = arg2[91 * steps + ((cycle - 1) & mask)];
      assert(x2160 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2161 = arg2[97 * steps + ((cycle - 1) & mask)];
      assert(x2161 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2162 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x2162 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2163 = x2159 - x2162;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2164 = (x2163 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x2165 = x7 - x2164;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[167 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2165);
          reg = x2165;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2166 = arg2[167 * steps + ((cycle - 0) & mask)];
      assert(x2166 != Fp::invalid());
      if (x2166 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2167 = arg2[148 * steps + ((cycle - 0) & mask)];
        assert(x2167 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x2168 = x6 - x2167;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x2168 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2169 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x2169 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2170 = x2169 - x2159;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2171 = x2170 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2172 = Fp(x2171.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2172);
            reg = x2172;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2173 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x2173 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2174 = x2171 - x2173;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2175 = x2174 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2176 = Fp(x2175.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2176);
            reg = x2176;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2177 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x2177 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2178 = x2175 - x2177;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2179 = x2178 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2180 = Fp(x2179.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2180);
            reg = x2180;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2181 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x2181 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2182 = x2179 - x2181;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2183 = x2182 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2183);
          reg = x2183;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x2184 = x2149 * x2161;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x2184 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x2185 = x7 - x2166;
      if (x2185 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2186 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x2186 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x2187 = x2159 - x2186;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x2187 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x2188 = x2154 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2189 = arg2[147 * steps + ((cycle - 0) & mask)];
        assert(x2189 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2190 = arg2[148 * steps + ((cycle - 0) & mask)];
        assert(x2190 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2191 = x2189 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2192 = x2191 + x2190;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2193 = x2192 - x2188;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2194 = x2193 + x2160;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2195 = Fp(x2194.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2195);
            reg = x2195;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2196 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x2196 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2197 = x2194 - x2196;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2198 = x2197 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2199 = Fp(x2198.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2199);
            reg = x2199;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2200 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x2200 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2201 = x2198 - x2200;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2202 = x2201 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2203 = Fp(x2202.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2203);
            reg = x2203;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2204 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x2204 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2205 = x2202 - x2204;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2206 = x2205 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2206);
          reg = x2206;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x2207 = x5 - x2190;
        if (x2207 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2208 = x2155 - x2150;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2208 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2209 = x2156 - x2151;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2209 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2210 = x2157 - x2152;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2210 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2211 = x2158 - x2153;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2211 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x2212 = arg2[148 * steps + ((cycle - 0) & mask)];
      assert(x2212 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x2213 = x6 - x2212;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x2214 = x7 - x2212;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x2215 = x5 - x2212;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x2216 = x2213 * x2215;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x2217 = x2214 * x2213;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x2218 = x2214 * x2215;
      if (x2218 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x2217 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x2216 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2161);
          reg = x2161;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x2219 = arg2[147 * steps + ((cycle - 0) & mask)];
      assert(x2219 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x2220 = arg2[146 * steps + ((cycle - 0) & mask)];
      assert(x2220 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2221 = arg2[156 * steps + ((cycle - 0) & mask)];
      assert(x2221 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2222 = arg2[157 * steps + ((cycle - 0) & mask)];
      assert(x2222 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2223 = arg2[158 * steps + ((cycle - 0) & mask)];
      assert(x2223 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2224 = arg2[159 * steps + ((cycle - 0) & mask)];
      assert(x2224 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2225 = arg2[168 * steps + ((cycle - 0) & mask)];
      assert(x2225 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2226 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x2226 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2227 = x2220 - x2226;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2228 = (x2227 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x2229 = x7 - x2228;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[169 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2229);
          reg = x2229;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2230 = arg2[169 * steps + ((cycle - 0) & mask)];
      assert(x2230 != Fp::invalid());
      if (x2230 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2231 = arg2[155 * steps + ((cycle - 0) & mask)];
        assert(x2231 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x2232 = x6 - x2231;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x2232 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2233 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x2233 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2234 = x2233 - x2220;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2235 = x2234 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2236 = Fp(x2235.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2236);
            reg = x2236;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2237 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x2237 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2238 = x2235 - x2237;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2239 = x2238 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2240 = Fp(x2239.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2240);
            reg = x2240;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2241 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x2241 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2242 = x2239 - x2241;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2243 = x2242 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2244 = Fp(x2243.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2244);
            reg = x2244;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2245 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x2245 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2246 = x2243 - x2245;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2247 = x2246 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2247);
          reg = x2247;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x2248 = x2149 * x2225;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x2248 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x2249 = x7 - x2230;
      if (x2249 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2250 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x2250 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x2251 = x2220 - x2250;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x2251 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x2252 = x2219 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2253 = arg2[154 * steps + ((cycle - 0) & mask)];
        assert(x2253 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2254 = arg2[155 * steps + ((cycle - 0) & mask)];
        assert(x2254 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2255 = x2253 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2256 = x2255 + x2254;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2257 = x2256 - x2252;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2258 = x2257 + x2212;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2259 = Fp(x2258.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2259);
            reg = x2259;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2260 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x2260 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2261 = x2258 - x2260;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2262 = x2261 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2263 = Fp(x2262.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2263);
            reg = x2263;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2264 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x2264 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2265 = x2262 - x2264;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2266 = x2265 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2267 = Fp(x2266.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2267);
            reg = x2267;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2268 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x2268 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2269 = x2266 - x2268;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2270 = x2269 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2270);
          reg = x2270;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x2271 = x5 - x2254;
        if (x2271 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2272 = x2150 - x2221;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2272 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2273 = x2151 - x2222;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2273 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2274 = x2152 - x2223;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2274 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2275 = x2153 - x2224;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2275 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x2276 = arg2[155 * steps + ((cycle - 0) & mask)];
      assert(x2276 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x2277 = x6 - x2276;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x2278 = x7 - x2276;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x2279 = x5 - x2276;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x2280 = x2277 * x2279;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x2281 = x2278 * x2277;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x2282 = x2278 * x2279;
      if (x2282 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x2281 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x2280 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2225);
          reg = x2225;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x2283 = arg2[154 * steps + ((cycle - 0) & mask)];
      assert(x2283 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x2284 = arg2[153 * steps + ((cycle - 0) & mask)];
      assert(x2284 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2285 = arg2[163 * steps + ((cycle - 0) & mask)];
      assert(x2285 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2286 = arg2[164 * steps + ((cycle - 0) & mask)];
      assert(x2286 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2287 = arg2[165 * steps + ((cycle - 0) & mask)];
      assert(x2287 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2288 = arg2[166 * steps + ((cycle - 0) & mask)];
      assert(x2288 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2289 = arg2[170 * steps + ((cycle - 0) & mask)];
      assert(x2289 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2290 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x2290 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2291 = x2284 - x2290;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2292 = (x2291 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x2293 = x7 - x2292;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[171 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2293);
          reg = x2293;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2294 = arg2[171 * steps + ((cycle - 0) & mask)];
      assert(x2294 != Fp::invalid());
      if (x2294 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2295 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x2295 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x2296 = x6 - x2295;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x2296 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2297 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x2297 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2298 = x2297 - x2284;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2299 = x2298 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2300 = Fp(x2299.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2300);
            reg = x2300;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2301 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x2301 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2302 = x2299 - x2301;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2303 = x2302 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2304 = Fp(x2303.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2304);
            reg = x2304;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2305 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x2305 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2306 = x2303 - x2305;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2307 = x2306 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2308 = Fp(x2307.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2308);
            reg = x2308;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2309 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x2309 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2310 = x2307 - x2309;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2311 = x2310 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2311);
          reg = x2311;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x2312 = x2149 * x2289;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x2312 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x2313 = x7 - x2294;
      if (x2313 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2314 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x2314 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x2315 = x2284 - x2314;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x2315 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x2316 = x2283 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2317 = arg2[161 * steps + ((cycle - 0) & mask)];
        assert(x2317 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2318 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x2318 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2319 = x2317 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2320 = x2319 + x2318;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2321 = x2320 - x2316;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2322 = x2321 + x2276;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2323 = Fp(x2322.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2323);
            reg = x2323;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2324 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x2324 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2325 = x2322 - x2324;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2326 = x2325 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2327 = Fp(x2326.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2327);
            reg = x2327;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2328 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x2328 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2329 = x2326 - x2328;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2330 = x2329 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2331 = Fp(x2330.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2331);
            reg = x2331;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2332 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x2332 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2333 = x2330 - x2332;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2334 = x2333 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2334);
          reg = x2334;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x2335 = x5 - x2318;
        if (x2335 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2336 = x2221 - x2285;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2336 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2337 = x2222 - x2286;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2337 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2338 = x2223 - x2287;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2338 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2339 = x2224 - x2288;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2339 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x2340 = arg2[162 * steps + ((cycle - 0) & mask)];
      assert(x2340 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x2341 = x6 - x2340;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x2342 = x7 - x2340;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x2343 = x5 - x2340;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x2344 = x2341 * x2343;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x2345 = x2342 * x2341;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x2346 = x2342 * x2343;
      if (x2346 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x2345 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x2344 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2289);
          reg = x2289;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x2347 = arg2[161 * steps + ((cycle - 0) & mask)];
      assert(x2347 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x2348 = arg2[160 * steps + ((cycle - 0) & mask)];
      assert(x2348 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2349 = arg2[92 * steps + ((cycle - 0) & mask)];
      assert(x2349 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2350 = arg2[93 * steps + ((cycle - 0) & mask)];
      assert(x2350 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2351 = arg2[94 * steps + ((cycle - 0) & mask)];
      assert(x2351 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2352 = arg2[95 * steps + ((cycle - 0) & mask)];
      assert(x2352 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/divide(DivideCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2353 = arg2[172 * steps + ((cycle - 0) & mask)];
      assert(x2353 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2354 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x2354 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2355 = x2348 - x2354;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2356 = (x2355 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x2357 = x7 - x2356;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[96 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2357);
          reg = x2357;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2358 = arg2[96 * steps + ((cycle - 0) & mask)];
      assert(x2358 != Fp::invalid());
      if (x2358 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2359 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x2359 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x2360 = x6 - x2359;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x2360 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2361 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x2361 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2362 = x2361 - x2348;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2363 = x2362 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2364 = Fp(x2363.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2364);
            reg = x2364;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2365 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x2365 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2366 = x2363 - x2365;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2367 = x2366 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2368 = Fp(x2367.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2368);
            reg = x2368;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2369 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x2369 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2370 = x2367 - x2369;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2371 = x2370 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2372 = Fp(x2371.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2372);
            reg = x2372;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2373 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x2373 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2374 = x2371 - x2373;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2375 = x2374 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2375);
          reg = x2375;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x2376 = x2149 * x2353;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x2376 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x2377 = x7 - x2358;
      if (x2377 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2378 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x2378 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x2379 = x2348 - x2378;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x2379 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x2380 = x2347 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2381 = arg2[90 * steps + ((cycle - 0) & mask)];
        assert(x2381 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2382 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x2382 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2383 = x2381 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2384 = x2383 + x2382;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2385 = x2384 - x2380;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2386 = x2385 + x2340;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2387 = Fp(x2386.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2387);
            reg = x2387;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2388 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x2388 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2389 = x2386 - x2388;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2390 = x2389 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2391 = Fp(x2390.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2391);
            reg = x2391;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2392 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x2392 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2393 = x2390 - x2392;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2394 = x2393 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2395 = Fp(x2394.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2395);
            reg = x2395;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2396 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x2396 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2397 = x2394 - x2396;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2398 = x2397 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2398);
          reg = x2398;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x2399 = x5 - x2382;
        if (x2399 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2400 = x2285 - x2349;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2400 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2401 = x2286 - x2350;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2401 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2402 = x2287 - x2351;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2402 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2403 = x2288 - x2352;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2403 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x2404 = arg2[91 * steps + ((cycle - 0) & mask)];
      assert(x2404 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x2405 = x6 - x2404;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x2406 = x7 - x2404;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x2407 = x5 - x2404;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x2408 = x2405 * x2407;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x2409 = x2406 * x2405;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x2410 = x2406 * x2407;
      if (x2410 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x2409 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x2408 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2353);
          reg = x2353;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x2411 = arg2[107 * steps + ((cycle - 0) & mask)];
    assert(x2411 != Fp::invalid());
    if (x2411 != 0) {
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2412 = arg2[89 * steps + ((cycle - 1) & mask)];
      assert(x2412 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2413 = arg2[90 * steps + ((cycle - 1) & mask)];
      assert(x2413 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2414 = arg2[91 * steps + ((cycle - 1) & mask)];
      assert(x2414 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2415 = arg2[92 * steps + ((cycle - 1) & mask)];
      assert(x2415 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2416 = arg2[93 * steps + ((cycle - 1) & mask)];
      assert(x2416 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2417 = arg2[94 * steps + ((cycle - 1) & mask)];
      assert(x2417 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2418 = arg2[95 * steps + ((cycle - 1) & mask)];
      assert(x2418 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":46:3)
      {
        auto& reg = arg2[89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2412);
        reg = x2412;
      }
      // loc("zirgen/components/ram.cpp":47:3)
      {
        auto& reg = arg2[90 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2413);
        reg = x2413;
      }
      // loc("zirgen/components/ram.cpp":48:3)
      {
        auto& reg = arg2[91 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2414);
        reg = x2414;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[92 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2415);
        reg = x2415;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[93 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2416);
        reg = x2416;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[94 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2417);
        reg = x2417;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[95 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2418);
        reg = x2418;
      }
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":102:10))
      auto x2419 = arg2[3 * steps + ((cycle - 1) & mask)];
      assert(x2419 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":102:10))
      auto x2420 = arg2[4 * steps + ((cycle - 1) & mask)];
      assert(x2420 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":102:10))
      auto x2421 = arg2[5 * steps + ((cycle - 1) & mask)];
      assert(x2421 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/extra(Twit)/twit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2422 = arg2[69 * steps + ((cycle - 1) & mask)];
      assert(x2422 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2423 = arg2[96 * steps + ((cycle - 1) & mask)];
      assert(x2423 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2424 = arg2[97 * steps + ((cycle - 1) & mask)];
      assert(x2424 != Fp::invalid());
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[96 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2423);
        reg = x2423;
      }
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[97 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2424);
        reg = x2424;
      }
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x2425 = Fp(x2419.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2425);
          reg = x2425;
        }
      }
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x2426 = Fp(x2420.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2426);
          reg = x2426;
        }
      }
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x2427 = Fp(x2421.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2427);
          reg = x2427;
        }
      }
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2422);
        reg = x2422;
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x2428 = arg2[108 * steps + ((cycle - 0) & mask)];
    assert(x2428 != Fp::invalid());
    if (x2428 != 0) {
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2429 = arg2[89 * steps + ((cycle - 1) & mask)];
      assert(x2429 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2430 = arg2[90 * steps + ((cycle - 1) & mask)];
      assert(x2430 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2431 = arg2[91 * steps + ((cycle - 1) & mask)];
      assert(x2431 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2432 = arg2[92 * steps + ((cycle - 1) & mask)];
      assert(x2432 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2433 = arg2[93 * steps + ((cycle - 1) & mask)];
      assert(x2433 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2434 = arg2[94 * steps + ((cycle - 1) & mask)];
      assert(x2434 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2435 = arg2[95 * steps + ((cycle - 1) & mask)];
      assert(x2435 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":46:3)
      {
        auto& reg = arg2[89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2429);
        reg = x2429;
      }
      // loc("zirgen/components/ram.cpp":47:3)
      {
        auto& reg = arg2[90 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2430);
        reg = x2430;
      }
      // loc("zirgen/components/ram.cpp":48:3)
      {
        auto& reg = arg2[91 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2431);
        reg = x2431;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[92 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2432);
        reg = x2432;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[93 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2433);
        reg = x2433;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[94 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2434);
        reg = x2434;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[95 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2435);
        reg = x2435;
      }
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":102:10))
      auto x2436 = arg2[3 * steps + ((cycle - 1) & mask)];
      assert(x2436 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":102:10))
      auto x2437 = arg2[4 * steps + ((cycle - 1) & mask)];
      assert(x2437 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":102:10))
      auto x2438 = arg2[5 * steps + ((cycle - 1) & mask)];
      assert(x2438 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/extra(Twit)/twit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2439 = arg2[69 * steps + ((cycle - 1) & mask)];
      assert(x2439 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2440 = arg2[96 * steps + ((cycle - 1) & mask)];
      assert(x2440 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2441 = arg2[97 * steps + ((cycle - 1) & mask)];
      assert(x2441 != Fp::invalid());
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[96 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2440);
        reg = x2440;
      }
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[97 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2441);
        reg = x2441;
      }
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x2442 = Fp(x2436.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2442);
          reg = x2442;
        }
      }
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x2443 = Fp(x2437.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2443);
          reg = x2443;
        }
      }
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x2444 = Fp(x2438.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2444);
          reg = x2444;
        }
      }
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2439);
        reg = x2439;
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x2445 = arg2[109 * steps + ((cycle - 0) & mask)];
    assert(x2445 != Fp::invalid());
    if (x2445 != 0) {
      {
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x2446 = extern_outs[0];
        auto x2447 = extern_outs[1];
        auto x2448 = extern_outs[2];
        auto x2449 = extern_outs[3];
        auto x2450 = extern_outs[4];
        auto x2451 = extern_outs[5];
        auto x2452 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2446);
          reg = x2446;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2447);
          reg = x2447;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2448);
          reg = x2448;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2449);
          reg = x2449;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2450);
          reg = x2450;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2451);
          reg = x2451;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2452);
          reg = x2452;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x2453 = extern_outs[0];
        auto x2454 = extern_outs[1];
        auto x2455 = extern_outs[2];
        auto x2456 = extern_outs[3];
        auto x2457 = extern_outs[4];
        auto x2458 = extern_outs[5];
        auto x2459 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2453);
          reg = x2453;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[161 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2454);
          reg = x2454;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[162 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2455);
          reg = x2455;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[163 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2456);
          reg = x2456;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[164 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2457);
          reg = x2457;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[165 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2458);
          reg = x2458;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[166 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2459);
          reg = x2459;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x2460 = extern_outs[0];
        auto x2461 = extern_outs[1];
        auto x2462 = extern_outs[2];
        auto x2463 = extern_outs[3];
        auto x2464 = extern_outs[4];
        auto x2465 = extern_outs[5];
        auto x2466 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[167 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2460);
          reg = x2460;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2461);
          reg = x2461;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[169 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2462);
          reg = x2462;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2463);
          reg = x2463;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[171 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2464);
          reg = x2464;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2465);
          reg = x2465;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[173 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2466);
          reg = x2466;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x2467 = extern_outs[0];
        auto x2468 = extern_outs[1];
        auto x2469 = extern_outs[2];
        auto x2470 = extern_outs[3];
        auto x2471 = extern_outs[4];
        auto x2472 = extern_outs[5];
        auto x2473 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[174 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2467);
          reg = x2467;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[175 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2468);
          reg = x2468;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[176 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2469);
          reg = x2469;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[177 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2470);
          reg = x2470;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[178 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2471);
          reg = x2471;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[179 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2472);
          reg = x2472;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[180 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2473);
          reg = x2473;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x2474 = extern_outs[0];
        auto x2475 = extern_outs[1];
        auto x2476 = extern_outs[2];
        auto x2477 = extern_outs[3];
        auto x2478 = extern_outs[4];
        auto x2479 = extern_outs[5];
        auto x2480 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[89 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2474);
          reg = x2474;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[90 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2475);
          reg = x2475;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[91 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2476);
          reg = x2476;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[92 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2477);
          reg = x2477;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[93 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2478);
          reg = x2478;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[94 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2479);
          reg = x2479;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[95 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2480);
          reg = x2480;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/global(Global)/sys_exit_code(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2481 = arg1[104];
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2482 = arg2[156 * steps + ((cycle - 0) & mask)];
      assert(x2482 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2483 = arg2[157 * steps + ((cycle - 0) & mask)];
      assert(x2483 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2484 = arg2[158 * steps + ((cycle - 0) & mask)];
      assert(x2484 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2485 = arg2[159 * steps + ((cycle - 0) & mask)];
      assert(x2485 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x2486 = arg2[90 * steps + ((cycle - 1) & mask)];
      assert(x2486 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2487 = arg2[92 * steps + ((cycle - 1) & mask)];
      assert(x2487 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2488 = arg2[93 * steps + ((cycle - 1) & mask)];
      assert(x2488 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2489 = arg2[94 * steps + ((cycle - 1) & mask)];
      assert(x2489 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2490 = arg2[95 * steps + ((cycle - 1) & mask)];
      assert(x2490 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x2491 = arg2[89 * steps + ((cycle - 1) & mask)];
      assert(x2491 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("zirgen/components/ram.cpp":67:42))
      auto x2492 = arg2[91 * steps + ((cycle - 1) & mask)];
      assert(x2492 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2493 = arg2[97 * steps + ((cycle - 1) & mask)];
      assert(x2493 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2494 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x2494 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2495 = x2491 - x2494;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2496 = (x2495 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x2497 = x7 - x2496;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[181 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2497);
          reg = x2497;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2498 = arg2[181 * steps + ((cycle - 0) & mask)];
      assert(x2498 != Fp::invalid());
      if (x2498 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2499 = arg2[155 * steps + ((cycle - 0) & mask)];
        assert(x2499 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x2500 = x6 - x2499;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x2500 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2501 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x2501 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2502 = x2501 - x2491;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2503 = x2502 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2504 = Fp(x2503.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2504);
            reg = x2504;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2505 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x2505 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2506 = x2503 - x2505;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2507 = x2506 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2508 = Fp(x2507.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2508);
            reg = x2508;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2509 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x2509 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2510 = x2507 - x2509;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2511 = x2510 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2512 = Fp(x2511.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2512);
            reg = x2512;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2513 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x2513 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2514 = x2511 - x2513;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2515 = x2514 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2515);
          reg = x2515;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x2516 = x2481 * x2493;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x2516 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x2517 = x7 - x2498;
      if (x2517 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2518 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x2518 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x2519 = x2491 - x2518;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x2519 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x2520 = x2486 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2521 = arg2[154 * steps + ((cycle - 0) & mask)];
        assert(x2521 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2522 = arg2[155 * steps + ((cycle - 0) & mask)];
        assert(x2522 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2523 = x2521 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2524 = x2523 + x2522;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2525 = x2524 - x2520;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2526 = x2525 + x2492;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2527 = Fp(x2526.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2527);
            reg = x2527;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2528 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x2528 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2529 = x2526 - x2528;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2530 = x2529 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2531 = Fp(x2530.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2531);
            reg = x2531;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2532 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x2532 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2533 = x2530 - x2532;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2534 = x2533 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2535 = Fp(x2534.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2535);
            reg = x2535;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2536 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x2536 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2537 = x2534 - x2536;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2538 = x2537 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2538);
          reg = x2538;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x2539 = x5 - x2522;
        if (x2539 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2540 = x2487 - x2482;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2540 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2541 = x2488 - x2483;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2541 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2542 = x2489 - x2484;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2542 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2543 = x2490 - x2485;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2543 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x2544 = arg2[155 * steps + ((cycle - 0) & mask)];
      assert(x2544 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x2545 = x6 - x2544;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x2546 = x7 - x2544;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x2547 = x5 - x2544;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x2548 = x2545 * x2547;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x2549 = x2546 * x2545;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x2550 = x2546 * x2547;
      if (x2550 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[182 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x2549 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[182 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x2548 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[182 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2493);
          reg = x2493;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x2551 = arg2[154 * steps + ((cycle - 0) & mask)];
      assert(x2551 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x2552 = arg2[153 * steps + ((cycle - 0) & mask)];
      assert(x2552 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2553 = arg2[163 * steps + ((cycle - 0) & mask)];
      assert(x2553 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2554 = arg2[164 * steps + ((cycle - 0) & mask)];
      assert(x2554 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2555 = arg2[165 * steps + ((cycle - 0) & mask)];
      assert(x2555 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2556 = arg2[166 * steps + ((cycle - 0) & mask)];
      assert(x2556 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2557 = arg2[182 * steps + ((cycle - 0) & mask)];
      assert(x2557 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2558 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x2558 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2559 = x2552 - x2558;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2560 = (x2559 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x2561 = x7 - x2560;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[183 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2561);
          reg = x2561;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2562 = arg2[183 * steps + ((cycle - 0) & mask)];
      assert(x2562 != Fp::invalid());
      if (x2562 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2563 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x2563 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x2564 = x6 - x2563;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x2564 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2565 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x2565 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2566 = x2565 - x2552;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2567 = x2566 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2568 = Fp(x2567.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2568);
            reg = x2568;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2569 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x2569 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2570 = x2567 - x2569;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2571 = x2570 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2572 = Fp(x2571.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2572);
            reg = x2572;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2573 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x2573 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2574 = x2571 - x2573;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2575 = x2574 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2576 = Fp(x2575.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2576);
            reg = x2576;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2577 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x2577 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2578 = x2575 - x2577;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2579 = x2578 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2579);
          reg = x2579;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x2580 = x2481 * x2557;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x2580 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x2581 = x7 - x2562;
      if (x2581 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2582 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x2582 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x2583 = x2552 - x2582;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x2583 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x2584 = x2551 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2585 = arg2[161 * steps + ((cycle - 0) & mask)];
        assert(x2585 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2586 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x2586 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2587 = x2585 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2588 = x2587 + x2586;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2589 = x2588 - x2584;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2590 = x2589 + x2544;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2591 = Fp(x2590.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2591);
            reg = x2591;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2592 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x2592 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2593 = x2590 - x2592;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2594 = x2593 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2595 = Fp(x2594.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2595);
            reg = x2595;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2596 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x2596 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2597 = x2594 - x2596;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2598 = x2597 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2599 = Fp(x2598.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2599);
            reg = x2599;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2600 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x2600 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2601 = x2598 - x2600;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2602 = x2601 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2602);
          reg = x2602;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x2603 = x5 - x2586;
        if (x2603 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2604 = x2482 - x2553;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2604 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2605 = x2483 - x2554;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2605 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2606 = x2484 - x2555;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2606 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2607 = x2485 - x2556;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2607 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x2608 = arg2[162 * steps + ((cycle - 0) & mask)];
      assert(x2608 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x2609 = x6 - x2608;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x2610 = x7 - x2608;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x2611 = x5 - x2608;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x2612 = x2609 * x2611;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x2613 = x2610 * x2609;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x2614 = x2610 * x2611;
      if (x2614 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[184 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x2613 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[184 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x2612 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[184 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2557);
          reg = x2557;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x2615 = arg2[161 * steps + ((cycle - 0) & mask)];
      assert(x2615 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x2616 = arg2[160 * steps + ((cycle - 0) & mask)];
      assert(x2616 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2617 = arg2[170 * steps + ((cycle - 0) & mask)];
      assert(x2617 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2618 = arg2[171 * steps + ((cycle - 0) & mask)];
      assert(x2618 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2619 = arg2[172 * steps + ((cycle - 0) & mask)];
      assert(x2619 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2620 = arg2[173 * steps + ((cycle - 0) & mask)];
      assert(x2620 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2621 = arg2[184 * steps + ((cycle - 0) & mask)];
      assert(x2621 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2622 = arg2[167 * steps + ((cycle - 0) & mask)];
        assert(x2622 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2623 = x2616 - x2622;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2624 = (x2623 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x2625 = x7 - x2624;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[185 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2625);
          reg = x2625;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2626 = arg2[185 * steps + ((cycle - 0) & mask)];
      assert(x2626 != Fp::invalid());
      if (x2626 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2627 = arg2[169 * steps + ((cycle - 0) & mask)];
        assert(x2627 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x2628 = x6 - x2627;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x2628 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2629 = arg2[167 * steps + ((cycle - 0) & mask)];
        assert(x2629 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2630 = x2629 - x2616;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2631 = x2630 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2632 = Fp(x2631.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2632);
            reg = x2632;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2633 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x2633 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2634 = x2631 - x2633;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2635 = x2634 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2636 = Fp(x2635.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2636);
            reg = x2636;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2637 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x2637 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2638 = x2635 - x2637;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2639 = x2638 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2640 = Fp(x2639.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2640);
            reg = x2640;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2641 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x2641 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2642 = x2639 - x2641;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2643 = x2642 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2643);
          reg = x2643;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x2644 = x2481 * x2621;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x2644 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x2645 = x7 - x2626;
      if (x2645 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2646 = arg2[167 * steps + ((cycle - 0) & mask)];
        assert(x2646 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x2647 = x2616 - x2646;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x2647 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x2648 = x2615 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2649 = arg2[168 * steps + ((cycle - 0) & mask)];
        assert(x2649 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2650 = arg2[169 * steps + ((cycle - 0) & mask)];
        assert(x2650 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2651 = x2649 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2652 = x2651 + x2650;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2653 = x2652 - x2648;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2654 = x2653 + x2608;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2655 = Fp(x2654.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2655);
            reg = x2655;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2656 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x2656 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2657 = x2654 - x2656;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2658 = x2657 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2659 = Fp(x2658.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2659);
            reg = x2659;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2660 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x2660 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2661 = x2658 - x2660;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2662 = x2661 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2663 = Fp(x2662.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2663);
            reg = x2663;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2664 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x2664 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2665 = x2662 - x2664;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2666 = x2665 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2666);
          reg = x2666;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x2667 = x5 - x2650;
        if (x2667 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2668 = x2553 - x2617;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2668 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2669 = x2554 - x2618;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2669 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2670 = x2555 - x2619;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2670 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2671 = x2556 - x2620;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2671 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x2672 = arg2[169 * steps + ((cycle - 0) & mask)];
      assert(x2672 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x2673 = x6 - x2672;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x2674 = x7 - x2672;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x2675 = x5 - x2672;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x2676 = x2673 * x2675;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x2677 = x2674 * x2673;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x2678 = x2674 * x2675;
      if (x2678 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[186 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x2677 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[186 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x2676 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[186 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2621);
          reg = x2621;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x2679 = arg2[168 * steps + ((cycle - 0) & mask)];
      assert(x2679 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x2680 = arg2[167 * steps + ((cycle - 0) & mask)];
      assert(x2680 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2681 = arg2[177 * steps + ((cycle - 0) & mask)];
      assert(x2681 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2682 = arg2[178 * steps + ((cycle - 0) & mask)];
      assert(x2682 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2683 = arg2[179 * steps + ((cycle - 0) & mask)];
      assert(x2683 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2684 = arg2[180 * steps + ((cycle - 0) & mask)];
      assert(x2684 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2685 = arg2[186 * steps + ((cycle - 0) & mask)];
      assert(x2685 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2686 = arg2[174 * steps + ((cycle - 0) & mask)];
        assert(x2686 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2687 = x2680 - x2686;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2688 = (x2687 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x2689 = x7 - x2688;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[187 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2689);
          reg = x2689;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2690 = arg2[187 * steps + ((cycle - 0) & mask)];
      assert(x2690 != Fp::invalid());
      if (x2690 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2691 = arg2[176 * steps + ((cycle - 0) & mask)];
        assert(x2691 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x2692 = x6 - x2691;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x2692 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2693 = arg2[174 * steps + ((cycle - 0) & mask)];
        assert(x2693 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2694 = x2693 - x2680;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2695 = x2694 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2696 = Fp(x2695.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2696);
            reg = x2696;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2697 = arg2[18 * steps + ((cycle - 0) & mask)];
        assert(x2697 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2698 = x2695 - x2697;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2699 = x2698 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2700 = Fp(x2699.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2700);
            reg = x2700;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2701 = arg2[19 * steps + ((cycle - 0) & mask)];
        assert(x2701 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2702 = x2699 - x2701;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2703 = x2702 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2704 = Fp(x2703.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2704);
            reg = x2704;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2705 = arg2[20 * steps + ((cycle - 0) & mask)];
        assert(x2705 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2706 = x2703 - x2705;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2707 = x2706 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2707);
          reg = x2707;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x2708 = x2481 * x2685;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x2708 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x2709 = x7 - x2690;
      if (x2709 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2710 = arg2[174 * steps + ((cycle - 0) & mask)];
        assert(x2710 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x2711 = x2680 - x2710;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x2711 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x2712 = x2679 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2713 = arg2[175 * steps + ((cycle - 0) & mask)];
        assert(x2713 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2714 = arg2[176 * steps + ((cycle - 0) & mask)];
        assert(x2714 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2715 = x2713 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2716 = x2715 + x2714;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2717 = x2716 - x2712;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2718 = x2717 + x2672;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2719 = Fp(x2718.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2719);
            reg = x2719;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2720 = arg2[18 * steps + ((cycle - 0) & mask)];
        assert(x2720 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2721 = x2718 - x2720;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2722 = x2721 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2723 = Fp(x2722.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2723);
            reg = x2723;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2724 = arg2[19 * steps + ((cycle - 0) & mask)];
        assert(x2724 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2725 = x2722 - x2724;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2726 = x2725 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2727 = Fp(x2726.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2727);
            reg = x2727;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2728 = arg2[20 * steps + ((cycle - 0) & mask)];
        assert(x2728 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2729 = x2726 - x2728;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2730 = x2729 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2730);
          reg = x2730;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x2731 = x5 - x2714;
        if (x2731 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2732 = x2617 - x2681;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2732 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2733 = x2618 - x2682;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2733 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2734 = x2619 - x2683;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2734 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2735 = x2620 - x2684;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2735 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x2736 = arg2[176 * steps + ((cycle - 0) & mask)];
      assert(x2736 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x2737 = x6 - x2736;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x2738 = x7 - x2736;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x2739 = x5 - x2736;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x2740 = x2737 * x2739;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x2741 = x2738 * x2737;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x2742 = x2738 * x2739;
      if (x2742 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[188 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x2741 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[188 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x2740 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[188 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2685);
          reg = x2685;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x2743 = arg2[175 * steps + ((cycle - 0) & mask)];
      assert(x2743 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x2744 = arg2[174 * steps + ((cycle - 0) & mask)];
      assert(x2744 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2745 = arg2[92 * steps + ((cycle - 0) & mask)];
      assert(x2745 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2746 = arg2[93 * steps + ((cycle - 0) & mask)];
      assert(x2746 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2747 = arg2[94 * steps + ((cycle - 0) & mask)];
      assert(x2747 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2748 = arg2[95 * steps + ((cycle - 0) & mask)];
      assert(x2748 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall(ECallCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2749 = arg2[188 * steps + ((cycle - 0) & mask)];
      assert(x2749 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2750 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x2750 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2751 = x2744 - x2750;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2752 = (x2751 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x2753 = x7 - x2752;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[96 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2753);
          reg = x2753;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2754 = arg2[96 * steps + ((cycle - 0) & mask)];
      assert(x2754 != Fp::invalid());
      if (x2754 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2755 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x2755 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x2756 = x6 - x2755;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x2756 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2757 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x2757 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2758 = x2757 - x2744;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2759 = x2758 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2760 = Fp(x2759.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2760);
            reg = x2760;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2761 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x2761 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2762 = x2759 - x2761;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2763 = x2762 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2764 = Fp(x2763.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2764);
            reg = x2764;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2765 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x2765 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2766 = x2763 - x2765;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2767 = x2766 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2768 = Fp(x2767.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2768);
            reg = x2768;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2769 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x2769 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2770 = x2767 - x2769;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2771 = x2770 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2771);
          reg = x2771;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x2772 = x2481 * x2749;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x2772 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x2773 = x7 - x2754;
      if (x2773 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2774 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x2774 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x2775 = x2744 - x2774;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x2775 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x2776 = x2743 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2777 = arg2[90 * steps + ((cycle - 0) & mask)];
        assert(x2777 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2778 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x2778 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2779 = x2777 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2780 = x2779 + x2778;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2781 = x2780 - x2776;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2782 = x2781 + x2736;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2783 = Fp(x2782.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2783);
            reg = x2783;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2784 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x2784 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2785 = x2782 - x2784;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2786 = x2785 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2787 = Fp(x2786.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2787);
            reg = x2787;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2788 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x2788 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2789 = x2786 - x2788;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2790 = x2789 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2791 = Fp(x2790.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2791);
            reg = x2791;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2792 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x2792 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2793 = x2790 - x2792;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2794 = x2793 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2794);
          reg = x2794;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x2795 = x5 - x2778;
        if (x2795 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2796 = x2681 - x2745;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2796 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2797 = x2682 - x2746;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2797 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2798 = x2683 - x2747;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2798 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2799 = x2684 - x2748;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2799 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x2800 = arg2[91 * steps + ((cycle - 0) & mask)];
      assert(x2800 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x2801 = x6 - x2800;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x2802 = x7 - x2800;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x2803 = x5 - x2800;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x2804 = x2801 * x2803;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x2805 = x2802 * x2801;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x2806 = x2802 * x2803;
      if (x2806 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x2805 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x2804 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2749);
          reg = x2749;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x2807 = arg2[110 * steps + ((cycle - 0) & mask)];
    assert(x2807 != Fp::invalid());
    if (x2807 != 0) {
      {
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x2808 = extern_outs[0];
        auto x2809 = extern_outs[1];
        auto x2810 = extern_outs[2];
        auto x2811 = extern_outs[3];
        auto x2812 = extern_outs[4];
        auto x2813 = extern_outs[5];
        auto x2814 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[132 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2808);
          reg = x2808;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[133 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2809);
          reg = x2809;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[134 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2810);
          reg = x2810;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[135 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2811);
          reg = x2811;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2812);
          reg = x2812;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2813);
          reg = x2813;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2814);
          reg = x2814;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x2815 = extern_outs[0];
        auto x2816 = extern_outs[1];
        auto x2817 = extern_outs[2];
        auto x2818 = extern_outs[3];
        auto x2819 = extern_outs[4];
        auto x2820 = extern_outs[5];
        auto x2821 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[89 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2815);
          reg = x2815;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[90 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2816);
          reg = x2816;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[91 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2817);
          reg = x2817;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[92 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2818);
          reg = x2818;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[93 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2819);
          reg = x2819;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[94 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2820);
          reg = x2820;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[95 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2821);
          reg = x2821;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/global(Global)/sys_exit_code(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2822 = arg1[104];
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_init(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2823 = arg2[135 * steps + ((cycle - 0) & mask)];
      assert(x2823 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_init(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2824 = arg2[136 * steps + ((cycle - 0) & mask)];
      assert(x2824 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_init(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2825 = arg2[137 * steps + ((cycle - 0) & mask)];
      assert(x2825 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_init(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2826 = arg2[138 * steps + ((cycle - 0) & mask)];
      assert(x2826 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x2827 = arg2[90 * steps + ((cycle - 1) & mask)];
      assert(x2827 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2828 = arg2[92 * steps + ((cycle - 1) & mask)];
      assert(x2828 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2829 = arg2[93 * steps + ((cycle - 1) & mask)];
      assert(x2829 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2830 = arg2[94 * steps + ((cycle - 1) & mask)];
      assert(x2830 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2831 = arg2[95 * steps + ((cycle - 1) & mask)];
      assert(x2831 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x2832 = arg2[89 * steps + ((cycle - 1) & mask)];
      assert(x2832 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("zirgen/components/ram.cpp":67:42))
      auto x2833 = arg2[91 * steps + ((cycle - 1) & mask)];
      assert(x2833 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2834 = arg2[97 * steps + ((cycle - 1) & mask)];
      assert(x2834 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_init(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2835 = arg2[132 * steps + ((cycle - 0) & mask)];
        assert(x2835 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2836 = x2832 - x2835;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2837 = (x2836 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x2838 = x7 - x2837;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2838);
          reg = x2838;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_init(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2839 = arg2[139 * steps + ((cycle - 0) & mask)];
      assert(x2839 != Fp::invalid());
      if (x2839 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_init(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2840 = arg2[134 * steps + ((cycle - 0) & mask)];
        assert(x2840 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x2841 = x6 - x2840;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x2841 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_init(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2842 = arg2[132 * steps + ((cycle - 0) & mask)];
        assert(x2842 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2843 = x2842 - x2832;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2844 = x2843 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2845 = Fp(x2844.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2845);
            reg = x2845;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2846 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x2846 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2847 = x2844 - x2846;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2848 = x2847 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2849 = Fp(x2848.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2849);
            reg = x2849;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2850 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x2850 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2851 = x2848 - x2850;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2852 = x2851 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2853 = Fp(x2852.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2853);
            reg = x2853;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2854 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x2854 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2855 = x2852 - x2854;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2856 = x2855 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2856);
          reg = x2856;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x2857 = x2822 * x2834;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x2857 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x2858 = x7 - x2839;
      if (x2858 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_init(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2859 = arg2[132 * steps + ((cycle - 0) & mask)];
        assert(x2859 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x2860 = x2832 - x2859;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x2860 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x2861 = x2827 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_init(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2862 = arg2[133 * steps + ((cycle - 0) & mask)];
        assert(x2862 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_init(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2863 = arg2[134 * steps + ((cycle - 0) & mask)];
        assert(x2863 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2864 = x2862 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2865 = x2864 + x2863;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2866 = x2865 - x2861;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2867 = x2866 + x2833;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2868 = Fp(x2867.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2868);
            reg = x2868;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2869 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x2869 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2870 = x2867 - x2869;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2871 = x2870 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2872 = Fp(x2871.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2872);
            reg = x2872;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2873 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x2873 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2874 = x2871 - x2873;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2875 = x2874 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2876 = Fp(x2875.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2876);
            reg = x2876;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2877 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x2877 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2878 = x2875 - x2877;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2879 = x2878 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2879);
          reg = x2879;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x2880 = x5 - x2863;
        if (x2880 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2881 = x2828 - x2823;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2881 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2882 = x2829 - x2824;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2882 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2883 = x2830 - x2825;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2883 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2884 = x2831 - x2826;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2884 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_init(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x2885 = arg2[134 * steps + ((cycle - 0) & mask)];
      assert(x2885 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x2886 = x6 - x2885;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x2887 = x7 - x2885;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x2888 = x5 - x2885;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x2889 = x2886 * x2888;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x2890 = x2887 * x2886;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x2891 = x2887 * x2888;
      if (x2891 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x2890 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x2889 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2834);
          reg = x2834;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_init(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x2892 = arg2[133 * steps + ((cycle - 0) & mask)];
      assert(x2892 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_init(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x2893 = arg2[132 * steps + ((cycle - 0) & mask)];
      assert(x2893 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2894 = arg2[92 * steps + ((cycle - 0) & mask)];
      assert(x2894 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2895 = arg2[93 * steps + ((cycle - 0) & mask)];
      assert(x2895 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2896 = arg2[94 * steps + ((cycle - 0) & mask)];
      assert(x2896 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2897 = arg2[95 * steps + ((cycle - 0) & mask)];
      assert(x2897 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_init(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2898 = arg2[140 * steps + ((cycle - 0) & mask)];
      assert(x2898 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2899 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x2899 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2900 = x2893 - x2899;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2901 = (x2900 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x2902 = x7 - x2901;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[96 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2902);
          reg = x2902;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2903 = arg2[96 * steps + ((cycle - 0) & mask)];
      assert(x2903 != Fp::invalid());
      if (x2903 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2904 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x2904 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x2905 = x6 - x2904;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x2905 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2906 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x2906 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2907 = x2906 - x2893;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2908 = x2907 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2909 = Fp(x2908.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2909);
            reg = x2909;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2910 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x2910 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2911 = x2908 - x2910;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2912 = x2911 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2913 = Fp(x2912.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2913);
            reg = x2913;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2914 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x2914 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2915 = x2912 - x2914;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2916 = x2915 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2917 = Fp(x2916.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2917);
            reg = x2917;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2918 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x2918 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2919 = x2916 - x2918;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2920 = x2919 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2920);
          reg = x2920;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x2921 = x2822 * x2898;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x2921 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x2922 = x7 - x2903;
      if (x2922 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2923 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x2923 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x2924 = x2893 - x2923;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x2924 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x2925 = x2892 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2926 = arg2[90 * steps + ((cycle - 0) & mask)];
        assert(x2926 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2927 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x2927 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2928 = x2926 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2929 = x2928 + x2927;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2930 = x2929 - x2925;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x2931 = x2930 + x2885;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2932 = Fp(x2931.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2932);
            reg = x2932;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2933 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x2933 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2934 = x2931 - x2933;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2935 = x2934 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2936 = Fp(x2935.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2936);
            reg = x2936;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2937 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x2937 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2938 = x2935 - x2937;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2939 = x2938 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2940 = Fp(x2939.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2940);
            reg = x2940;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2941 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x2941 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2942 = x2939 - x2941;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2943 = x2942 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2943);
          reg = x2943;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x2944 = x5 - x2927;
        if (x2944 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2945 = x2823 - x2894;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2945 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2946 = x2824 - x2895;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2946 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2947 = x2825 - x2896;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2947 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x2948 = x2826 - x2897;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x2948 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x2949 = arg2[91 * steps + ((cycle - 0) & mask)];
      assert(x2949 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x2950 = x6 - x2949;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x2951 = x7 - x2949;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x2952 = x5 - x2949;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x2953 = x2950 * x2952;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x2954 = x2951 * x2950;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x2955 = x2951 * x2952;
      if (x2955 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x2954 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x2953 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2898);
          reg = x2898;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x2956 = arg2[111 * steps + ((cycle - 0) & mask)];
    assert(x2956 != Fp::invalid());
    if (x2956 != 0) {
      {
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x2957 = extern_outs[0];
        auto x2958 = extern_outs[1];
        auto x2959 = extern_outs[2];
        auto x2960 = extern_outs[3];
        auto x2961 = extern_outs[4];
        auto x2962 = extern_outs[5];
        auto x2963 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[132 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2957);
          reg = x2957;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[133 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2958);
          reg = x2958;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[134 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2959);
          reg = x2959;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[135 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2960);
          reg = x2960;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2961);
          reg = x2961;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2962);
          reg = x2962;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2963);
          reg = x2963;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x2964 = extern_outs[0];
        auto x2965 = extern_outs[1];
        auto x2966 = extern_outs[2];
        auto x2967 = extern_outs[3];
        auto x2968 = extern_outs[4];
        auto x2969 = extern_outs[5];
        auto x2970 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[89 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2964);
          reg = x2964;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[90 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2965);
          reg = x2965;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[91 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2966);
          reg = x2966;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[92 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2967);
          reg = x2967;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[93 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2968);
          reg = x2968;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[94 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2969);
          reg = x2969;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[95 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2970);
          reg = x2970;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/global(Global)/sys_exit_code(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2971 = arg1[104];
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_load(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2972 = arg2[135 * steps + ((cycle - 0) & mask)];
      assert(x2972 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_load(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2973 = arg2[136 * steps + ((cycle - 0) & mask)];
      assert(x2973 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_load(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2974 = arg2[137 * steps + ((cycle - 0) & mask)];
      assert(x2974 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_load(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2975 = arg2[138 * steps + ((cycle - 0) & mask)];
      assert(x2975 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x2976 = arg2[90 * steps + ((cycle - 1) & mask)];
      assert(x2976 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2977 = arg2[92 * steps + ((cycle - 1) & mask)];
      assert(x2977 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2978 = arg2[93 * steps + ((cycle - 1) & mask)];
      assert(x2978 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2979 = arg2[94 * steps + ((cycle - 1) & mask)];
      assert(x2979 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2980 = arg2[95 * steps + ((cycle - 1) & mask)];
      assert(x2980 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x2981 = arg2[89 * steps + ((cycle - 1) & mask)];
      assert(x2981 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("zirgen/components/ram.cpp":67:42))
      auto x2982 = arg2[91 * steps + ((cycle - 1) & mask)];
      assert(x2982 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2983 = arg2[97 * steps + ((cycle - 1) & mask)];
      assert(x2983 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_load(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2984 = arg2[132 * steps + ((cycle - 0) & mask)];
        assert(x2984 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2985 = x2981 - x2984;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x2986 = (x2985 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x2987 = x7 - x2986;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2987);
          reg = x2987;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_load(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x2988 = arg2[139 * steps + ((cycle - 0) & mask)];
      assert(x2988 != Fp::invalid());
      if (x2988 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_load(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2989 = arg2[134 * steps + ((cycle - 0) & mask)];
        assert(x2989 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x2990 = x6 - x2989;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x2990 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_load(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x2991 = arg2[132 * steps + ((cycle - 0) & mask)];
        assert(x2991 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2992 = x2991 - x2981;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x2993 = x2992 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2994 = Fp(x2993.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2994);
            reg = x2994;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2995 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x2995 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x2996 = x2993 - x2995;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x2997 = x2996 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x2998 = Fp(x2997.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2998);
            reg = x2998;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x2999 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x2999 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3000 = x2997 - x2999;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3001 = x3000 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3002 = Fp(x3001.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3002);
            reg = x3002;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3003 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x3003 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3004 = x3001 - x3003;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3005 = x3004 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3005);
          reg = x3005;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x3006 = x2971 * x2983;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x3006 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x3007 = x7 - x2988;
      if (x3007 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_load(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3008 = arg2[132 * steps + ((cycle - 0) & mask)];
        assert(x3008 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x3009 = x2981 - x3008;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x3009 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x3010 = x2976 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_load(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3011 = arg2[133 * steps + ((cycle - 0) & mask)];
        assert(x3011 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_load(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3012 = arg2[134 * steps + ((cycle - 0) & mask)];
        assert(x3012 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3013 = x3011 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3014 = x3013 + x3012;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3015 = x3014 - x3010;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3016 = x3015 + x2982;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3017 = Fp(x3016.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3017);
            reg = x3017;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3018 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x3018 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3019 = x3016 - x3018;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3020 = x3019 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3021 = Fp(x3020.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3021);
            reg = x3021;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3022 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x3022 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3023 = x3020 - x3022;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3024 = x3023 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3025 = Fp(x3024.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3025);
            reg = x3025;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3026 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x3026 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3027 = x3024 - x3026;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3028 = x3027 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3028);
          reg = x3028;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x3029 = x5 - x3012;
        if (x3029 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3030 = x2977 - x2972;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3030 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3031 = x2978 - x2973;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3031 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3032 = x2979 - x2974;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3032 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3033 = x2980 - x2975;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3033 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_load(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x3034 = arg2[134 * steps + ((cycle - 0) & mask)];
      assert(x3034 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x3035 = x6 - x3034;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x3036 = x7 - x3034;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x3037 = x5 - x3034;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x3038 = x3035 * x3037;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x3039 = x3036 * x3035;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x3040 = x3036 * x3037;
      if (x3040 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x3039 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x3038 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2983);
          reg = x2983;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_load(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x3041 = arg2[133 * steps + ((cycle - 0) & mask)];
      assert(x3041 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_load(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x3042 = arg2[132 * steps + ((cycle - 0) & mask)];
      assert(x3042 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3043 = arg2[92 * steps + ((cycle - 0) & mask)];
      assert(x3043 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3044 = arg2[93 * steps + ((cycle - 0) & mask)];
      assert(x3044 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3045 = arg2[94 * steps + ((cycle - 0) & mask)];
      assert(x3045 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3046 = arg2[95 * steps + ((cycle - 0) & mask)];
      assert(x3046 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_load(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3047 = arg2[140 * steps + ((cycle - 0) & mask)];
      assert(x3047 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3048 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x3048 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3049 = x3042 - x3048;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3050 = (x3049 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x3051 = x7 - x3050;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[96 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3051);
          reg = x3051;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3052 = arg2[96 * steps + ((cycle - 0) & mask)];
      assert(x3052 != Fp::invalid());
      if (x3052 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3053 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x3053 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x3054 = x6 - x3053;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x3054 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3055 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x3055 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3056 = x3055 - x3042;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3057 = x3056 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3058 = Fp(x3057.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3058);
            reg = x3058;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3059 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x3059 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3060 = x3057 - x3059;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3061 = x3060 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3062 = Fp(x3061.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3062);
            reg = x3062;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3063 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x3063 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3064 = x3061 - x3063;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3065 = x3064 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3066 = Fp(x3065.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3066);
            reg = x3066;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3067 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x3067 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3068 = x3065 - x3067;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3069 = x3068 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3069);
          reg = x3069;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x3070 = x2971 * x3047;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x3070 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x3071 = x7 - x3052;
      if (x3071 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3072 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x3072 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x3073 = x3042 - x3072;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x3073 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x3074 = x3041 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3075 = arg2[90 * steps + ((cycle - 0) & mask)];
        assert(x3075 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3076 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x3076 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3077 = x3075 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3078 = x3077 + x3076;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3079 = x3078 - x3074;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3080 = x3079 + x3034;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3081 = Fp(x3080.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3081);
            reg = x3081;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3082 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x3082 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3083 = x3080 - x3082;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3084 = x3083 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3085 = Fp(x3084.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3085);
            reg = x3085;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3086 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x3086 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3087 = x3084 - x3086;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3088 = x3087 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3089 = Fp(x3088.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3089);
            reg = x3089;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3090 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x3090 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3091 = x3088 - x3090;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3092 = x3091 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3092);
          reg = x3092;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x3093 = x5 - x3076;
        if (x3093 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3094 = x2972 - x3043;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3094 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3095 = x2973 - x3044;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3095 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3096 = x2974 - x3045;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3096 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3097 = x2975 - x3046;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3097 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x3098 = arg2[91 * steps + ((cycle - 0) & mask)];
      assert(x3098 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x3099 = x6 - x3098;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x3100 = x7 - x3098;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x3101 = x5 - x3098;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x3102 = x3099 * x3101;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x3103 = x3100 * x3099;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x3104 = x3100 * x3101;
      if (x3104 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x3103 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x3102 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3047);
          reg = x3047;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x3105 = arg2[112 * steps + ((cycle - 0) & mask)];
    assert(x3105 != Fp::invalid());
    if (x3105 != 0) {
      {
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x3106 = extern_outs[0];
        auto x3107 = extern_outs[1];
        auto x3108 = extern_outs[2];
        auto x3109 = extern_outs[3];
        auto x3110 = extern_outs[4];
        auto x3111 = extern_outs[5];
        auto x3112 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[132 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3106);
          reg = x3106;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[133 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3107);
          reg = x3107;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[134 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3108);
          reg = x3108;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[135 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3109);
          reg = x3109;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3110);
          reg = x3110;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3111);
          reg = x3111;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3112);
          reg = x3112;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x3113 = extern_outs[0];
        auto x3114 = extern_outs[1];
        auto x3115 = extern_outs[2];
        auto x3116 = extern_outs[3];
        auto x3117 = extern_outs[4];
        auto x3118 = extern_outs[5];
        auto x3119 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[89 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3113);
          reg = x3113;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[90 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3114);
          reg = x3114;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[91 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3115);
          reg = x3115;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[92 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3116);
          reg = x3116;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[93 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3117);
          reg = x3117;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[94 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3118);
          reg = x3118;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[95 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3119);
          reg = x3119;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/global(Global)/sys_exit_code(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3120 = arg1[104];
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_main(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3121 = arg2[135 * steps + ((cycle - 0) & mask)];
      assert(x3121 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_main(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3122 = arg2[136 * steps + ((cycle - 0) & mask)];
      assert(x3122 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_main(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3123 = arg2[137 * steps + ((cycle - 0) & mask)];
      assert(x3123 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_main(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3124 = arg2[138 * steps + ((cycle - 0) & mask)];
      assert(x3124 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x3125 = arg2[90 * steps + ((cycle - 1) & mask)];
      assert(x3125 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3126 = arg2[92 * steps + ((cycle - 1) & mask)];
      assert(x3126 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3127 = arg2[93 * steps + ((cycle - 1) & mask)];
      assert(x3127 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3128 = arg2[94 * steps + ((cycle - 1) & mask)];
      assert(x3128 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3129 = arg2[95 * steps + ((cycle - 1) & mask)];
      assert(x3129 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x3130 = arg2[89 * steps + ((cycle - 1) & mask)];
      assert(x3130 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("zirgen/components/ram.cpp":67:42))
      auto x3131 = arg2[91 * steps + ((cycle - 1) & mask)];
      assert(x3131 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3132 = arg2[97 * steps + ((cycle - 1) & mask)];
      assert(x3132 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_main(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3133 = arg2[132 * steps + ((cycle - 0) & mask)];
        assert(x3133 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3134 = x3130 - x3133;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3135 = (x3134 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x3136 = x7 - x3135;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3136);
          reg = x3136;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_main(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3137 = arg2[139 * steps + ((cycle - 0) & mask)];
      assert(x3137 != Fp::invalid());
      if (x3137 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_main(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3138 = arg2[134 * steps + ((cycle - 0) & mask)];
        assert(x3138 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x3139 = x6 - x3138;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x3139 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_main(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3140 = arg2[132 * steps + ((cycle - 0) & mask)];
        assert(x3140 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3141 = x3140 - x3130;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3142 = x3141 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3143 = Fp(x3142.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3143);
            reg = x3143;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3144 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x3144 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3145 = x3142 - x3144;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3146 = x3145 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3147 = Fp(x3146.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3147);
            reg = x3147;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3148 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x3148 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3149 = x3146 - x3148;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3150 = x3149 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3151 = Fp(x3150.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3151);
            reg = x3151;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3152 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x3152 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3153 = x3150 - x3152;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3154 = x3153 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3154);
          reg = x3154;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x3155 = x3120 * x3132;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x3155 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x3156 = x7 - x3137;
      if (x3156 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_main(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3157 = arg2[132 * steps + ((cycle - 0) & mask)];
        assert(x3157 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x3158 = x3130 - x3157;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x3158 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x3159 = x3125 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_main(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3160 = arg2[133 * steps + ((cycle - 0) & mask)];
        assert(x3160 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_main(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3161 = arg2[134 * steps + ((cycle - 0) & mask)];
        assert(x3161 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3162 = x3160 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3163 = x3162 + x3161;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3164 = x3163 - x3159;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3165 = x3164 + x3131;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3166 = Fp(x3165.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3166);
            reg = x3166;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3167 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x3167 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3168 = x3165 - x3167;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3169 = x3168 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3170 = Fp(x3169.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3170);
            reg = x3170;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3171 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x3171 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3172 = x3169 - x3171;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3173 = x3172 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3174 = Fp(x3173.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3174);
            reg = x3174;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3175 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x3175 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3176 = x3173 - x3175;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3177 = x3176 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3177);
          reg = x3177;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x3178 = x5 - x3161;
        if (x3178 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3179 = x3126 - x3121;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3179 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3180 = x3127 - x3122;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3180 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3181 = x3128 - x3123;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3181 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3182 = x3129 - x3124;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3182 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_main(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x3183 = arg2[134 * steps + ((cycle - 0) & mask)];
      assert(x3183 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x3184 = x6 - x3183;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x3185 = x7 - x3183;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x3186 = x5 - x3183;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x3187 = x3184 * x3186;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x3188 = x3185 * x3184;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x3189 = x3185 * x3186;
      if (x3189 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x3188 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x3187 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3132);
          reg = x3132;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_main(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x3190 = arg2[133 * steps + ((cycle - 0) & mask)];
      assert(x3190 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_main(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x3191 = arg2[132 * steps + ((cycle - 0) & mask)];
      assert(x3191 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3192 = arg2[92 * steps + ((cycle - 0) & mask)];
      assert(x3192 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3193 = arg2[93 * steps + ((cycle - 0) & mask)];
      assert(x3193 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3194 = arg2[94 * steps + ((cycle - 0) & mask)];
      assert(x3194 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3195 = arg2[95 * steps + ((cycle - 0) & mask)];
      assert(x3195 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/sha_main(ShaWrap)/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3196 = arg2[140 * steps + ((cycle - 0) & mask)];
      assert(x3196 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3197 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x3197 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3198 = x3191 - x3197;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3199 = (x3198 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x3200 = x7 - x3199;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[96 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3200);
          reg = x3200;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3201 = arg2[96 * steps + ((cycle - 0) & mask)];
      assert(x3201 != Fp::invalid());
      if (x3201 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3202 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x3202 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x3203 = x6 - x3202;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x3203 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3204 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x3204 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3205 = x3204 - x3191;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3206 = x3205 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3207 = Fp(x3206.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3207);
            reg = x3207;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3208 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x3208 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3209 = x3206 - x3208;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3210 = x3209 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3211 = Fp(x3210.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3211);
            reg = x3211;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3212 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x3212 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3213 = x3210 - x3212;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3214 = x3213 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3215 = Fp(x3214.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3215);
            reg = x3215;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3216 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x3216 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3217 = x3214 - x3216;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3218 = x3217 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3218);
          reg = x3218;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x3219 = x3120 * x3196;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x3219 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x3220 = x7 - x3201;
      if (x3220 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3221 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x3221 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x3222 = x3191 - x3221;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x3222 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x3223 = x3190 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3224 = arg2[90 * steps + ((cycle - 0) & mask)];
        assert(x3224 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3225 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x3225 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3226 = x3224 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3227 = x3226 + x3225;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3228 = x3227 - x3223;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3229 = x3228 + x3183;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3230 = Fp(x3229.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3230);
            reg = x3230;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3231 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x3231 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3232 = x3229 - x3231;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3233 = x3232 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3234 = Fp(x3233.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3234);
            reg = x3234;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3235 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x3235 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3236 = x3233 - x3235;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3237 = x3236 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3238 = Fp(x3237.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3238);
            reg = x3238;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3239 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x3239 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3240 = x3237 - x3239;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3241 = x3240 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3241);
          reg = x3241;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x3242 = x5 - x3225;
        if (x3242 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3243 = x3121 - x3192;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3243 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3244 = x3122 - x3193;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3244 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3245 = x3123 - x3194;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3245 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3246 = x3124 - x3195;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3246 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x3247 = arg2[91 * steps + ((cycle - 0) & mask)];
      assert(x3247 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x3248 = x6 - x3247;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x3249 = x7 - x3247;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x3250 = x5 - x3247;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x3251 = x3248 * x3250;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x3252 = x3249 * x3248;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x3253 = x3249 * x3250;
      if (x3253 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x3252 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x3251 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3196);
          reg = x3196;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x3254 = arg2[113 * steps + ((cycle - 0) & mask)];
    assert(x3254 != Fp::invalid());
    if (x3254 != 0) {
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3255 = arg2[89 * steps + ((cycle - 1) & mask)];
      assert(x3255 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3256 = arg2[90 * steps + ((cycle - 1) & mask)];
      assert(x3256 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3257 = arg2[91 * steps + ((cycle - 1) & mask)];
      assert(x3257 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3258 = arg2[92 * steps + ((cycle - 1) & mask)];
      assert(x3258 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3259 = arg2[93 * steps + ((cycle - 1) & mask)];
      assert(x3259 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3260 = arg2[94 * steps + ((cycle - 1) & mask)];
      assert(x3260 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3261 = arg2[95 * steps + ((cycle - 1) & mask)];
      assert(x3261 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":46:3)
      {
        auto& reg = arg2[89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3255);
        reg = x3255;
      }
      // loc("zirgen/components/ram.cpp":47:3)
      {
        auto& reg = arg2[90 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3256);
        reg = x3256;
      }
      // loc("zirgen/components/ram.cpp":48:3)
      {
        auto& reg = arg2[91 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3257);
        reg = x3257;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[92 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3258);
        reg = x3258;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[93 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3259);
        reg = x3259;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[94 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3260);
        reg = x3260;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[95 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3261);
        reg = x3261;
      }
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":102:10))
      auto x3262 = arg2[3 * steps + ((cycle - 1) & mask)];
      assert(x3262 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":102:10))
      auto x3263 = arg2[4 * steps + ((cycle - 1) & mask)];
      assert(x3263 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":102:10))
      auto x3264 = arg2[5 * steps + ((cycle - 1) & mask)];
      assert(x3264 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/extra(Twit)/twit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3265 = arg2[69 * steps + ((cycle - 1) & mask)];
      assert(x3265 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3266 = arg2[96 * steps + ((cycle - 1) & mask)];
      assert(x3266 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3267 = arg2[97 * steps + ((cycle - 1) & mask)];
      assert(x3267 != Fp::invalid());
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[96 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3266);
        reg = x3266;
      }
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[97 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3267);
        reg = x3267;
      }
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x3268 = Fp(x3262.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3268);
          reg = x3268;
        }
      }
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x3269 = Fp(x3263.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3269);
          reg = x3269;
        }
      }
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x3270 = Fp(x3264.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3270);
          reg = x3270;
        }
      }
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3265);
        reg = x3265;
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x3271 = arg2[114 * steps + ((cycle - 0) & mask)];
    assert(x3271 != Fp::invalid());
    if (x3271 != 0) {
      {
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x3272 = extern_outs[0];
        auto x3273 = extern_outs[1];
        auto x3274 = extern_outs[2];
        auto x3275 = extern_outs[3];
        auto x3276 = extern_outs[4];
        auto x3277 = extern_outs[5];
        auto x3278 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3272);
          reg = x3272;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3273);
          reg = x3273;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3274);
          reg = x3274;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3275);
          reg = x3275;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3276);
          reg = x3276;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3277);
          reg = x3277;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3278);
          reg = x3278;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x3279 = extern_outs[0];
        auto x3280 = extern_outs[1];
        auto x3281 = extern_outs[2];
        auto x3282 = extern_outs[3];
        auto x3283 = extern_outs[4];
        auto x3284 = extern_outs[5];
        auto x3285 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3279);
          reg = x3279;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3280);
          reg = x3280;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3281);
          reg = x3281;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3282);
          reg = x3282;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3283);
          reg = x3283;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3284);
          reg = x3284;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3285);
          reg = x3285;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x3286 = extern_outs[0];
        auto x3287 = extern_outs[1];
        auto x3288 = extern_outs[2];
        auto x3289 = extern_outs[3];
        auto x3290 = extern_outs[4];
        auto x3291 = extern_outs[5];
        auto x3292 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3286);
          reg = x3286;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[161 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3287);
          reg = x3287;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[162 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3288);
          reg = x3288;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[163 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3289);
          reg = x3289;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[164 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3290);
          reg = x3290;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[165 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3291);
          reg = x3291;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[166 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3292);
          reg = x3292;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x3293 = extern_outs[0];
        auto x3294 = extern_outs[1];
        auto x3295 = extern_outs[2];
        auto x3296 = extern_outs[3];
        auto x3297 = extern_outs[4];
        auto x3298 = extern_outs[5];
        auto x3299 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[89 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3293);
          reg = x3293;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[90 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3294);
          reg = x3294;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[91 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3295);
          reg = x3295;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[92 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3296);
          reg = x3296;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[93 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3297);
          reg = x3297;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[94 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3298);
          reg = x3298;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[95 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3299);
          reg = x3299;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/global(Global)/sys_exit_code(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3300 = arg1[104];
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3301 = arg2[149 * steps + ((cycle - 0) & mask)];
      assert(x3301 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3302 = arg2[150 * steps + ((cycle - 0) & mask)];
      assert(x3302 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3303 = arg2[151 * steps + ((cycle - 0) & mask)];
      assert(x3303 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3304 = arg2[152 * steps + ((cycle - 0) & mask)];
      assert(x3304 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x3305 = arg2[90 * steps + ((cycle - 1) & mask)];
      assert(x3305 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3306 = arg2[92 * steps + ((cycle - 1) & mask)];
      assert(x3306 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3307 = arg2[93 * steps + ((cycle - 1) & mask)];
      assert(x3307 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3308 = arg2[94 * steps + ((cycle - 1) & mask)];
      assert(x3308 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3309 = arg2[95 * steps + ((cycle - 1) & mask)];
      assert(x3309 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x3310 = arg2[89 * steps + ((cycle - 1) & mask)];
      assert(x3310 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("zirgen/components/ram.cpp":67:42))
      auto x3311 = arg2[91 * steps + ((cycle - 1) & mask)];
      assert(x3311 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3312 = arg2[97 * steps + ((cycle - 1) & mask)];
      assert(x3312 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3313 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x3313 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3314 = x3310 - x3313;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3315 = (x3314 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x3316 = x7 - x3315;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[167 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3316);
          reg = x3316;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3317 = arg2[167 * steps + ((cycle - 0) & mask)];
      assert(x3317 != Fp::invalid());
      if (x3317 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3318 = arg2[148 * steps + ((cycle - 0) & mask)];
        assert(x3318 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x3319 = x6 - x3318;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x3319 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3320 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x3320 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3321 = x3320 - x3310;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3322 = x3321 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3323 = Fp(x3322.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3323);
            reg = x3323;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3324 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x3324 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3325 = x3322 - x3324;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3326 = x3325 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3327 = Fp(x3326.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3327);
            reg = x3327;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3328 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x3328 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3329 = x3326 - x3328;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3330 = x3329 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3331 = Fp(x3330.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3331);
            reg = x3331;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3332 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x3332 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3333 = x3330 - x3332;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3334 = x3333 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3334);
          reg = x3334;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x3335 = x3300 * x3312;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x3335 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x3336 = x7 - x3317;
      if (x3336 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3337 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x3337 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x3338 = x3310 - x3337;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x3338 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x3339 = x3305 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3340 = arg2[147 * steps + ((cycle - 0) & mask)];
        assert(x3340 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3341 = arg2[148 * steps + ((cycle - 0) & mask)];
        assert(x3341 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3342 = x3340 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3343 = x3342 + x3341;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3344 = x3343 - x3339;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3345 = x3344 + x3311;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3346 = Fp(x3345.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3346);
            reg = x3346;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3347 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x3347 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3348 = x3345 - x3347;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3349 = x3348 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3350 = Fp(x3349.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3350);
            reg = x3350;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3351 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x3351 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3352 = x3349 - x3351;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3353 = x3352 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3354 = Fp(x3353.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3354);
            reg = x3354;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3355 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x3355 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3356 = x3353 - x3355;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3357 = x3356 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3357);
          reg = x3357;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x3358 = x5 - x3341;
        if (x3358 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3359 = x3306 - x3301;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3359 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3360 = x3307 - x3302;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3360 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3361 = x3308 - x3303;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3361 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3362 = x3309 - x3304;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3362 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x3363 = arg2[148 * steps + ((cycle - 0) & mask)];
      assert(x3363 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x3364 = x6 - x3363;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x3365 = x7 - x3363;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x3366 = x5 - x3363;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x3367 = x3364 * x3366;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x3368 = x3365 * x3364;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x3369 = x3365 * x3366;
      if (x3369 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x3368 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x3367 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3312);
          reg = x3312;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x3370 = arg2[147 * steps + ((cycle - 0) & mask)];
      assert(x3370 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x3371 = arg2[146 * steps + ((cycle - 0) & mask)];
      assert(x3371 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3372 = arg2[156 * steps + ((cycle - 0) & mask)];
      assert(x3372 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3373 = arg2[157 * steps + ((cycle - 0) & mask)];
      assert(x3373 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3374 = arg2[158 * steps + ((cycle - 0) & mask)];
      assert(x3374 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3375 = arg2[159 * steps + ((cycle - 0) & mask)];
      assert(x3375 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3376 = arg2[168 * steps + ((cycle - 0) & mask)];
      assert(x3376 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3377 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x3377 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3378 = x3371 - x3377;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3379 = (x3378 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x3380 = x7 - x3379;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[169 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3380);
          reg = x3380;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3381 = arg2[169 * steps + ((cycle - 0) & mask)];
      assert(x3381 != Fp::invalid());
      if (x3381 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3382 = arg2[155 * steps + ((cycle - 0) & mask)];
        assert(x3382 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x3383 = x6 - x3382;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x3383 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3384 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x3384 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3385 = x3384 - x3371;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3386 = x3385 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3387 = Fp(x3386.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3387);
            reg = x3387;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3388 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x3388 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3389 = x3386 - x3388;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3390 = x3389 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3391 = Fp(x3390.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3391);
            reg = x3391;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3392 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x3392 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3393 = x3390 - x3392;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3394 = x3393 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3395 = Fp(x3394.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3395);
            reg = x3395;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3396 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x3396 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3397 = x3394 - x3396;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3398 = x3397 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3398);
          reg = x3398;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x3399 = x3300 * x3376;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x3399 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x3400 = x7 - x3381;
      if (x3400 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3401 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x3401 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x3402 = x3371 - x3401;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x3402 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x3403 = x3370 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3404 = arg2[154 * steps + ((cycle - 0) & mask)];
        assert(x3404 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3405 = arg2[155 * steps + ((cycle - 0) & mask)];
        assert(x3405 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3406 = x3404 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3407 = x3406 + x3405;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3408 = x3407 - x3403;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3409 = x3408 + x3363;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3410 = Fp(x3409.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3410);
            reg = x3410;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3411 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x3411 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3412 = x3409 - x3411;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3413 = x3412 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3414 = Fp(x3413.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3414);
            reg = x3414;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3415 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x3415 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3416 = x3413 - x3415;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3417 = x3416 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3418 = Fp(x3417.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3418);
            reg = x3418;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3419 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x3419 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3420 = x3417 - x3419;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3421 = x3420 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3421);
          reg = x3421;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x3422 = x5 - x3405;
        if (x3422 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3423 = x3301 - x3372;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3423 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3424 = x3302 - x3373;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3424 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3425 = x3303 - x3374;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3425 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3426 = x3304 - x3375;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3426 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x3427 = arg2[155 * steps + ((cycle - 0) & mask)];
      assert(x3427 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x3428 = x6 - x3427;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x3429 = x7 - x3427;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x3430 = x5 - x3427;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x3431 = x3428 * x3430;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x3432 = x3429 * x3428;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x3433 = x3429 * x3430;
      if (x3433 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x3432 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x3431 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3376);
          reg = x3376;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x3434 = arg2[154 * steps + ((cycle - 0) & mask)];
      assert(x3434 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x3435 = arg2[153 * steps + ((cycle - 0) & mask)];
      assert(x3435 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3436 = arg2[163 * steps + ((cycle - 0) & mask)];
      assert(x3436 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3437 = arg2[164 * steps + ((cycle - 0) & mask)];
      assert(x3437 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3438 = arg2[165 * steps + ((cycle - 0) & mask)];
      assert(x3438 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3439 = arg2[166 * steps + ((cycle - 0) & mask)];
      assert(x3439 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3440 = arg2[170 * steps + ((cycle - 0) & mask)];
      assert(x3440 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3441 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x3441 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3442 = x3435 - x3441;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3443 = (x3442 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x3444 = x7 - x3443;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[171 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3444);
          reg = x3444;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3445 = arg2[171 * steps + ((cycle - 0) & mask)];
      assert(x3445 != Fp::invalid());
      if (x3445 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3446 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x3446 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x3447 = x6 - x3446;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x3447 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3448 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x3448 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3449 = x3448 - x3435;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3450 = x3449 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3451 = Fp(x3450.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3451);
            reg = x3451;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3452 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x3452 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3453 = x3450 - x3452;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3454 = x3453 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3455 = Fp(x3454.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3455);
            reg = x3455;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3456 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x3456 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3457 = x3454 - x3456;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3458 = x3457 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3459 = Fp(x3458.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3459);
            reg = x3459;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3460 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x3460 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3461 = x3458 - x3460;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3462 = x3461 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3462);
          reg = x3462;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x3463 = x3300 * x3440;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x3463 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x3464 = x7 - x3445;
      if (x3464 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3465 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x3465 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x3466 = x3435 - x3465;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x3466 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x3467 = x3434 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3468 = arg2[161 * steps + ((cycle - 0) & mask)];
        assert(x3468 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3469 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x3469 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3470 = x3468 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3471 = x3470 + x3469;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3472 = x3471 - x3467;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3473 = x3472 + x3427;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3474 = Fp(x3473.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3474);
            reg = x3474;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3475 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x3475 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3476 = x3473 - x3475;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3477 = x3476 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3478 = Fp(x3477.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3478);
            reg = x3478;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3479 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x3479 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3480 = x3477 - x3479;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3481 = x3480 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3482 = Fp(x3481.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3482);
            reg = x3482;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3483 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x3483 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3484 = x3481 - x3483;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3485 = x3484 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3485);
          reg = x3485;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x3486 = x5 - x3469;
        if (x3486 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3487 = x3372 - x3436;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3487 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3488 = x3373 - x3437;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3488 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3489 = x3374 - x3438;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3489 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3490 = x3375 - x3439;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3490 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x3491 = arg2[162 * steps + ((cycle - 0) & mask)];
      assert(x3491 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x3492 = x6 - x3491;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x3493 = x7 - x3491;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x3494 = x5 - x3491;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x3495 = x3492 * x3494;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x3496 = x3493 * x3492;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x3497 = x3493 * x3494;
      if (x3497 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x3496 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x3495 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3440);
          reg = x3440;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x3498 = arg2[161 * steps + ((cycle - 0) & mask)];
      assert(x3498 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x3499 = arg2[160 * steps + ((cycle - 0) & mask)];
      assert(x3499 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3500 = arg2[92 * steps + ((cycle - 0) & mask)];
      assert(x3500 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3501 = arg2[93 * steps + ((cycle - 0) & mask)];
      assert(x3501 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3502 = arg2[94 * steps + ((cycle - 0) & mask)];
      assert(x3502 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3503 = arg2[95 * steps + ((cycle - 0) & mask)];
      assert(x3503 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/ecall_copy_in(ECallCopyInCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3504 = arg2[172 * steps + ((cycle - 0) & mask)];
      assert(x3504 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3505 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x3505 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3506 = x3499 - x3505;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3507 = (x3506 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x3508 = x7 - x3507;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[96 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3508);
          reg = x3508;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3509 = arg2[96 * steps + ((cycle - 0) & mask)];
      assert(x3509 != Fp::invalid());
      if (x3509 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3510 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x3510 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x3511 = x6 - x3510;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x3511 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3512 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x3512 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3513 = x3512 - x3499;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3514 = x3513 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3515 = Fp(x3514.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3515);
            reg = x3515;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3516 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x3516 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3517 = x3514 - x3516;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3518 = x3517 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3519 = Fp(x3518.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3519);
            reg = x3519;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3520 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x3520 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3521 = x3518 - x3520;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3522 = x3521 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3523 = Fp(x3522.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3523);
            reg = x3523;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3524 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x3524 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3525 = x3522 - x3524;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3526 = x3525 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3526);
          reg = x3526;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x3527 = x3300 * x3504;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x3527 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x3528 = x7 - x3509;
      if (x3528 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3529 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x3529 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x3530 = x3499 - x3529;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x3530 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x3531 = x3498 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3532 = arg2[90 * steps + ((cycle - 0) & mask)];
        assert(x3532 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3533 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x3533 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3534 = x3532 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3535 = x3534 + x3533;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3536 = x3535 - x3531;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3537 = x3536 + x3491;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3538 = Fp(x3537.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3538);
            reg = x3538;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3539 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x3539 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3540 = x3537 - x3539;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3541 = x3540 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3542 = Fp(x3541.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3542);
            reg = x3542;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3543 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x3543 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3544 = x3541 - x3543;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3545 = x3544 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3546 = Fp(x3545.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3546);
            reg = x3546;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3547 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x3547 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3548 = x3545 - x3547;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3549 = x3548 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3549);
          reg = x3549;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x3550 = x5 - x3533;
        if (x3550 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3551 = x3436 - x3500;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3551 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3552 = x3437 - x3501;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3552 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3553 = x3438 - x3502;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3553 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3554 = x3439 - x3503;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3554 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x3555 = arg2[91 * steps + ((cycle - 0) & mask)];
      assert(x3555 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x3556 = x6 - x3555;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x3557 = x7 - x3555;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x3558 = x5 - x3555;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x3559 = x3556 * x3558;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x3560 = x3557 * x3556;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x3561 = x3557 * x3558;
      if (x3561 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x3560 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x3559 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3504);
          reg = x3504;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x3562 = arg2[115 * steps + ((cycle - 0) & mask)];
    assert(x3562 != Fp::invalid());
    if (x3562 != 0) {
      {
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x3563 = extern_outs[0];
        auto x3564 = extern_outs[1];
        auto x3565 = extern_outs[2];
        auto x3566 = extern_outs[3];
        auto x3567 = extern_outs[4];
        auto x3568 = extern_outs[5];
        auto x3569 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3563);
          reg = x3563;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3564);
          reg = x3564;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3565);
          reg = x3565;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3566);
          reg = x3566;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3567);
          reg = x3567;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3568);
          reg = x3568;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3569);
          reg = x3569;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x3570 = extern_outs[0];
        auto x3571 = extern_outs[1];
        auto x3572 = extern_outs[2];
        auto x3573 = extern_outs[3];
        auto x3574 = extern_outs[4];
        auto x3575 = extern_outs[5];
        auto x3576 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3570);
          reg = x3570;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3571);
          reg = x3571;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3572);
          reg = x3572;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3573);
          reg = x3573;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3574);
          reg = x3574;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3575);
          reg = x3575;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3576);
          reg = x3576;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x3577 = extern_outs[0];
        auto x3578 = extern_outs[1];
        auto x3579 = extern_outs[2];
        auto x3580 = extern_outs[3];
        auto x3581 = extern_outs[4];
        auto x3582 = extern_outs[5];
        auto x3583 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3577);
          reg = x3577;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[161 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3578);
          reg = x3578;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[162 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3579);
          reg = x3579;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[163 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3580);
          reg = x3580;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[164 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3581);
          reg = x3581;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[165 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3582);
          reg = x3582;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[166 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3583);
          reg = x3583;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x3584 = extern_outs[0];
        auto x3585 = extern_outs[1];
        auto x3586 = extern_outs[2];
        auto x3587 = extern_outs[3];
        auto x3588 = extern_outs[4];
        auto x3589 = extern_outs[5];
        auto x3590 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[89 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3584);
          reg = x3584;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[90 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3585);
          reg = x3585;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[91 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3586);
          reg = x3586;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[92 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3587);
          reg = x3587;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[93 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3588);
          reg = x3588;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[94 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3589);
          reg = x3589;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[95 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3590);
          reg = x3590;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/global(Global)/sys_exit_code(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3591 = arg1[104];
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3592 = arg2[149 * steps + ((cycle - 0) & mask)];
      assert(x3592 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3593 = arg2[150 * steps + ((cycle - 0) & mask)];
      assert(x3593 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3594 = arg2[151 * steps + ((cycle - 0) & mask)];
      assert(x3594 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3595 = arg2[152 * steps + ((cycle - 0) & mask)];
      assert(x3595 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x3596 = arg2[90 * steps + ((cycle - 1) & mask)];
      assert(x3596 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3597 = arg2[92 * steps + ((cycle - 1) & mask)];
      assert(x3597 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3598 = arg2[93 * steps + ((cycle - 1) & mask)];
      assert(x3598 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3599 = arg2[94 * steps + ((cycle - 1) & mask)];
      assert(x3599 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3600 = arg2[95 * steps + ((cycle - 1) & mask)];
      assert(x3600 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x3601 = arg2[89 * steps + ((cycle - 1) & mask)];
      assert(x3601 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("zirgen/components/ram.cpp":67:42))
      auto x3602 = arg2[91 * steps + ((cycle - 1) & mask)];
      assert(x3602 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3603 = arg2[97 * steps + ((cycle - 1) & mask)];
      assert(x3603 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3604 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x3604 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3605 = x3601 - x3604;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3606 = (x3605 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x3607 = x7 - x3606;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[167 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3607);
          reg = x3607;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3608 = arg2[167 * steps + ((cycle - 0) & mask)];
      assert(x3608 != Fp::invalid());
      if (x3608 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3609 = arg2[148 * steps + ((cycle - 0) & mask)];
        assert(x3609 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x3610 = x6 - x3609;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x3610 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3611 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x3611 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3612 = x3611 - x3601;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3613 = x3612 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3614 = Fp(x3613.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3614);
            reg = x3614;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3615 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x3615 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3616 = x3613 - x3615;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3617 = x3616 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3618 = Fp(x3617.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3618);
            reg = x3618;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3619 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x3619 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3620 = x3617 - x3619;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3621 = x3620 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3622 = Fp(x3621.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3622);
            reg = x3622;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3623 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x3623 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3624 = x3621 - x3623;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3625 = x3624 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3625);
          reg = x3625;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x3626 = x3591 * x3603;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x3626 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x3627 = x7 - x3608;
      if (x3627 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3628 = arg2[146 * steps + ((cycle - 0) & mask)];
        assert(x3628 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x3629 = x3601 - x3628;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x3629 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x3630 = x3596 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3631 = arg2[147 * steps + ((cycle - 0) & mask)];
        assert(x3631 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3632 = arg2[148 * steps + ((cycle - 0) & mask)];
        assert(x3632 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3633 = x3631 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3634 = x3633 + x3632;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3635 = x3634 - x3630;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3636 = x3635 + x3602;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3637 = Fp(x3636.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3637);
            reg = x3637;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3638 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x3638 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3639 = x3636 - x3638;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3640 = x3639 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3641 = Fp(x3640.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3641);
            reg = x3641;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3642 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x3642 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3643 = x3640 - x3642;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3644 = x3643 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3645 = Fp(x3644.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3645);
            reg = x3645;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3646 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x3646 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3647 = x3644 - x3646;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3648 = x3647 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3648);
          reg = x3648;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x3649 = x5 - x3632;
        if (x3649 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3650 = x3597 - x3592;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3650 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3651 = x3598 - x3593;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3651 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3652 = x3599 - x3594;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3652 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3653 = x3600 - x3595;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3653 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x3654 = arg2[148 * steps + ((cycle - 0) & mask)];
      assert(x3654 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x3655 = x6 - x3654;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x3656 = x7 - x3654;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x3657 = x5 - x3654;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x3658 = x3655 * x3657;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x3659 = x3656 * x3655;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x3660 = x3656 * x3657;
      if (x3660 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x3659 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x3658 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3603);
          reg = x3603;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x3661 = arg2[147 * steps + ((cycle - 0) & mask)];
      assert(x3661 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x3662 = arg2[146 * steps + ((cycle - 0) & mask)];
      assert(x3662 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3663 = arg2[156 * steps + ((cycle - 0) & mask)];
      assert(x3663 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3664 = arg2[157 * steps + ((cycle - 0) & mask)];
      assert(x3664 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3665 = arg2[158 * steps + ((cycle - 0) & mask)];
      assert(x3665 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3666 = arg2[159 * steps + ((cycle - 0) & mask)];
      assert(x3666 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3667 = arg2[168 * steps + ((cycle - 0) & mask)];
      assert(x3667 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3668 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x3668 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3669 = x3662 - x3668;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3670 = (x3669 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x3671 = x7 - x3670;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[169 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3671);
          reg = x3671;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3672 = arg2[169 * steps + ((cycle - 0) & mask)];
      assert(x3672 != Fp::invalid());
      if (x3672 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3673 = arg2[155 * steps + ((cycle - 0) & mask)];
        assert(x3673 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x3674 = x6 - x3673;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x3674 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3675 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x3675 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3676 = x3675 - x3662;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3677 = x3676 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3678 = Fp(x3677.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3678);
            reg = x3678;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3679 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x3679 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3680 = x3677 - x3679;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3681 = x3680 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3682 = Fp(x3681.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3682);
            reg = x3682;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3683 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x3683 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3684 = x3681 - x3683;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3685 = x3684 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3686 = Fp(x3685.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3686);
            reg = x3686;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3687 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x3687 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3688 = x3685 - x3687;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3689 = x3688 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3689);
          reg = x3689;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x3690 = x3591 * x3667;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x3690 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x3691 = x7 - x3672;
      if (x3691 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3692 = arg2[153 * steps + ((cycle - 0) & mask)];
        assert(x3692 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x3693 = x3662 - x3692;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x3693 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x3694 = x3661 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3695 = arg2[154 * steps + ((cycle - 0) & mask)];
        assert(x3695 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3696 = arg2[155 * steps + ((cycle - 0) & mask)];
        assert(x3696 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3697 = x3695 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3698 = x3697 + x3696;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3699 = x3698 - x3694;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3700 = x3699 + x3654;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3701 = Fp(x3700.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3701);
            reg = x3701;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3702 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x3702 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3703 = x3700 - x3702;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3704 = x3703 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3705 = Fp(x3704.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3705);
            reg = x3705;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3706 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x3706 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3707 = x3704 - x3706;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3708 = x3707 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3709 = Fp(x3708.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3709);
            reg = x3709;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3710 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x3710 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3711 = x3708 - x3710;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3712 = x3711 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3712);
          reg = x3712;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x3713 = x5 - x3696;
        if (x3713 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3714 = x3592 - x3663;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3714 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3715 = x3593 - x3664;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3715 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3716 = x3594 - x3665;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3716 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3717 = x3595 - x3666;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3717 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x3718 = arg2[155 * steps + ((cycle - 0) & mask)];
      assert(x3718 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x3719 = x6 - x3718;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x3720 = x7 - x3718;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x3721 = x5 - x3718;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x3722 = x3719 * x3721;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x3723 = x3720 * x3719;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x3724 = x3720 * x3721;
      if (x3724 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x3723 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x3722 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3667);
          reg = x3667;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x3725 = arg2[154 * steps + ((cycle - 0) & mask)];
      assert(x3725 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x3726 = arg2[153 * steps + ((cycle - 0) & mask)];
      assert(x3726 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3727 = arg2[163 * steps + ((cycle - 0) & mask)];
      assert(x3727 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3728 = arg2[164 * steps + ((cycle - 0) & mask)];
      assert(x3728 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3729 = arg2[165 * steps + ((cycle - 0) & mask)];
      assert(x3729 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3730 = arg2[166 * steps + ((cycle - 0) & mask)];
      assert(x3730 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3731 = arg2[170 * steps + ((cycle - 0) & mask)];
      assert(x3731 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3732 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x3732 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3733 = x3726 - x3732;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3734 = (x3733 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x3735 = x7 - x3734;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[171 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3735);
          reg = x3735;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3736 = arg2[171 * steps + ((cycle - 0) & mask)];
      assert(x3736 != Fp::invalid());
      if (x3736 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3737 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x3737 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x3738 = x6 - x3737;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x3738 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3739 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x3739 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3740 = x3739 - x3726;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3741 = x3740 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3742 = Fp(x3741.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3742);
            reg = x3742;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3743 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x3743 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3744 = x3741 - x3743;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3745 = x3744 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3746 = Fp(x3745.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3746);
            reg = x3746;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3747 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x3747 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3748 = x3745 - x3747;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3749 = x3748 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3750 = Fp(x3749.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3750);
            reg = x3750;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3751 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x3751 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3752 = x3749 - x3751;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3753 = x3752 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3753);
          reg = x3753;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x3754 = x3591 * x3731;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x3754 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x3755 = x7 - x3736;
      if (x3755 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3756 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x3756 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x3757 = x3726 - x3756;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x3757 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x3758 = x3725 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3759 = arg2[161 * steps + ((cycle - 0) & mask)];
        assert(x3759 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3760 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x3760 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3761 = x3759 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3762 = x3761 + x3760;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3763 = x3762 - x3758;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3764 = x3763 + x3718;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3765 = Fp(x3764.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3765);
            reg = x3765;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3766 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x3766 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3767 = x3764 - x3766;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3768 = x3767 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3769 = Fp(x3768.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3769);
            reg = x3769;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3770 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x3770 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3771 = x3768 - x3770;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3772 = x3771 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3773 = Fp(x3772.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3773);
            reg = x3773;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3774 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x3774 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3775 = x3772 - x3774;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3776 = x3775 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3776);
          reg = x3776;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x3777 = x5 - x3760;
        if (x3777 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3778 = x3663 - x3727;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3778 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3779 = x3664 - x3728;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3779 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3780 = x3665 - x3729;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3780 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3781 = x3666 - x3730;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3781 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x3782 = arg2[162 * steps + ((cycle - 0) & mask)];
      assert(x3782 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x3783 = x6 - x3782;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x3784 = x7 - x3782;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x3785 = x5 - x3782;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x3786 = x3783 * x3785;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x3787 = x3784 * x3783;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x3788 = x3784 * x3785;
      if (x3788 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x3787 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x3786 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3731);
          reg = x3731;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x3789 = arg2[161 * steps + ((cycle - 0) & mask)];
      assert(x3789 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x3790 = arg2[160 * steps + ((cycle - 0) & mask)];
      assert(x3790 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3791 = arg2[92 * steps + ((cycle - 0) & mask)];
      assert(x3791 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3792 = arg2[93 * steps + ((cycle - 0) & mask)];
      assert(x3792 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3793 = arg2[94 * steps + ((cycle - 0) & mask)];
      assert(x3793 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3794 = arg2[95 * steps + ((cycle - 0) & mask)];
      assert(x3794 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int(BigIntCycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3795 = arg2[172 * steps + ((cycle - 0) & mask)];
      assert(x3795 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3796 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x3796 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3797 = x3790 - x3796;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3798 = (x3797 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x3799 = x7 - x3798;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[96 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3799);
          reg = x3799;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3800 = arg2[96 * steps + ((cycle - 0) & mask)];
      assert(x3800 != Fp::invalid());
      if (x3800 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3801 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x3801 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x3802 = x6 - x3801;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x3802 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3803 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x3803 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3804 = x3803 - x3790;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3805 = x3804 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3806 = Fp(x3805.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3806);
            reg = x3806;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3807 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x3807 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3808 = x3805 - x3807;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3809 = x3808 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3810 = Fp(x3809.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3810);
            reg = x3810;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3811 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x3811 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3812 = x3809 - x3811;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3813 = x3812 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3814 = Fp(x3813.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3814);
            reg = x3814;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3815 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x3815 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3816 = x3813 - x3815;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3817 = x3816 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3817);
          reg = x3817;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x3818 = x3591 * x3795;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x3818 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x3819 = x7 - x3800;
      if (x3819 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3820 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x3820 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x3821 = x3790 - x3820;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x3821 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x3822 = x3789 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3823 = arg2[90 * steps + ((cycle - 0) & mask)];
        assert(x3823 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3824 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x3824 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3825 = x3823 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3826 = x3825 + x3824;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3827 = x3826 - x3822;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3828 = x3827 + x3782;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3829 = Fp(x3828.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3829);
            reg = x3829;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3830 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x3830 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3831 = x3828 - x3830;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3832 = x3831 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3833 = Fp(x3832.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3833);
            reg = x3833;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3834 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x3834 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3835 = x3832 - x3834;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3836 = x3835 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3837 = Fp(x3836.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3837);
            reg = x3837;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3838 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x3838 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3839 = x3836 - x3838;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3840 = x3839 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3840);
          reg = x3840;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x3841 = x5 - x3824;
        if (x3841 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3842 = x3727 - x3791;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3842 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3843 = x3728 - x3792;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3843 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3844 = x3729 - x3793;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3844 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3845 = x3730 - x3794;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3845 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x3846 = arg2[91 * steps + ((cycle - 0) & mask)];
      assert(x3846 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x3847 = x6 - x3846;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x3848 = x7 - x3846;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x3849 = x5 - x3846;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x3850 = x3847 * x3849;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x3851 = x3848 * x3847;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x3852 = x3848 * x3849;
      if (x3852 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x3851 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x3850 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3795);
          reg = x3795;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x3853 = arg2[116 * steps + ((cycle - 0) & mask)];
    assert(x3853 != Fp::invalid());
    if (x3853 != 0) {
      {
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x3854 = extern_outs[0];
        auto x3855 = extern_outs[1];
        auto x3856 = extern_outs[2];
        auto x3857 = extern_outs[3];
        auto x3858 = extern_outs[4];
        auto x3859 = extern_outs[5];
        auto x3860 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3854);
          reg = x3854;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[161 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3855);
          reg = x3855;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[162 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3856);
          reg = x3856;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[163 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3857);
          reg = x3857;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[164 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3858);
          reg = x3858;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[165 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3859);
          reg = x3859;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[166 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3860);
          reg = x3860;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x3861 = extern_outs[0];
        auto x3862 = extern_outs[1];
        auto x3863 = extern_outs[2];
        auto x3864 = extern_outs[3];
        auto x3865 = extern_outs[4];
        auto x3866 = extern_outs[5];
        auto x3867 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[167 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3861);
          reg = x3861;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3862);
          reg = x3862;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[169 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3863);
          reg = x3863;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3864);
          reg = x3864;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[171 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3865);
          reg = x3865;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3866);
          reg = x3866;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[173 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3867);
          reg = x3867;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x3868 = extern_outs[0];
        auto x3869 = extern_outs[1];
        auto x3870 = extern_outs[2];
        auto x3871 = extern_outs[3];
        auto x3872 = extern_outs[4];
        auto x3873 = extern_outs[5];
        auto x3874 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[174 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3868);
          reg = x3868;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[175 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3869);
          reg = x3869;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[176 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3870);
          reg = x3870;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[177 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3871);
          reg = x3871;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[178 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3872);
          reg = x3872;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[179 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3873);
          reg = x3873;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[180 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3874);
          reg = x3874;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x3875 = extern_outs[0];
        auto x3876 = extern_outs[1];
        auto x3877 = extern_outs[2];
        auto x3878 = extern_outs[3];
        auto x3879 = extern_outs[4];
        auto x3880 = extern_outs[5];
        auto x3881 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[181 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3875);
          reg = x3875;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[182 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3876);
          reg = x3876;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[183 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3877);
          reg = x3877;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[184 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3878);
          reg = x3878;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[185 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3879);
          reg = x3879;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[186 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3880);
          reg = x3880;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[187 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3881);
          reg = x3881;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x3882 = extern_outs[0];
        auto x3883 = extern_outs[1];
        auto x3884 = extern_outs[2];
        auto x3885 = extern_outs[3];
        auto x3886 = extern_outs[4];
        auto x3887 = extern_outs[5];
        auto x3888 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[188 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3882);
          reg = x3882;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[189 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3883);
          reg = x3883;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[190 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3884);
          reg = x3884;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[191 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3885);
          reg = x3885;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[192 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3886);
          reg = x3886;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[193 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3887);
          reg = x3887;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[194 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3888);
          reg = x3888;
        }
        extern_plonkRead_ram(ctx, cycle, "ram", extern_args, extern_outs);
        auto x3889 = extern_outs[0];
        auto x3890 = extern_outs[1];
        auto x3891 = extern_outs[2];
        auto x3892 = extern_outs[3];
        auto x3893 = extern_outs[4];
        auto x3894 = extern_outs[5];
        auto x3895 = extern_outs[6];
        // loc("zirgen/components/ram.cpp":46:3)
        {
          auto& reg = arg2[89 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3889);
          reg = x3889;
        }
        // loc("zirgen/components/ram.cpp":47:3)
        {
          auto& reg = arg2[90 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3890);
          reg = x3890;
        }
        // loc("zirgen/components/ram.cpp":48:3)
        {
          auto& reg = arg2[91 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3891);
          reg = x3891;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[92 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3892);
          reg = x3892;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[93 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3893);
          reg = x3893;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[94 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3894);
          reg = x3894;
        }
        // loc("zirgen/components/u32.cpp":98:5)
        {
          auto& reg = arg2[95 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3895);
          reg = x3895;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/global(Global)/sys_exit_code(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3896 = arg1[104];
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3897 = arg2[163 * steps + ((cycle - 0) & mask)];
      assert(x3897 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3898 = arg2[164 * steps + ((cycle - 0) & mask)];
      assert(x3898 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3899 = arg2[165 * steps + ((cycle - 0) & mask)];
      assert(x3899 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3900 = arg2[166 * steps + ((cycle - 0) & mask)];
      assert(x3900 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x3901 = arg2[90 * steps + ((cycle - 1) & mask)];
      assert(x3901 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3902 = arg2[92 * steps + ((cycle - 1) & mask)];
      assert(x3902 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3903 = arg2[93 * steps + ((cycle - 1) & mask)];
      assert(x3903 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3904 = arg2[94 * steps + ((cycle - 1) & mask)];
      assert(x3904 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3905 = arg2[95 * steps + ((cycle - 1) & mask)];
      assert(x3905 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x3906 = arg2[89 * steps + ((cycle - 1) & mask)];
      assert(x3906 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("zirgen/components/ram.cpp":67:42))
      auto x3907 = arg2[91 * steps + ((cycle - 1) & mask)];
      assert(x3907 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3908 = arg2[97 * steps + ((cycle - 1) & mask)];
      assert(x3908 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3909 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x3909 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3910 = x3906 - x3909;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3911 = (x3910 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x3912 = x7 - x3911;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[195 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3912);
          reg = x3912;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3913 = arg2[195 * steps + ((cycle - 0) & mask)];
      assert(x3913 != Fp::invalid());
      if (x3913 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3914 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x3914 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x3915 = x6 - x3914;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x3915 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3916 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x3916 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3917 = x3916 - x3906;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3918 = x3917 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3919 = Fp(x3918.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3919);
            reg = x3919;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3920 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x3920 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3921 = x3918 - x3920;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3922 = x3921 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3923 = Fp(x3922.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3923);
            reg = x3923;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3924 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x3924 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3925 = x3922 - x3924;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3926 = x3925 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3927 = Fp(x3926.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3927);
            reg = x3927;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3928 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x3928 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3929 = x3926 - x3928;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3930 = x3929 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3930);
          reg = x3930;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x3931 = x3896 * x3908;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x3931 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x3932 = x7 - x3913;
      if (x3932 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3933 = arg2[160 * steps + ((cycle - 0) & mask)];
        assert(x3933 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x3934 = x3906 - x3933;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x3934 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x3935 = x3901 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3936 = arg2[161 * steps + ((cycle - 0) & mask)];
        assert(x3936 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3937 = arg2[162 * steps + ((cycle - 0) & mask)];
        assert(x3937 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3938 = x3936 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3939 = x3938 + x3937;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3940 = x3939 - x3935;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x3941 = x3940 + x3907;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3942 = Fp(x3941.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[9 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3942);
            reg = x3942;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3943 = arg2[9 * steps + ((cycle - 0) & mask)];
        assert(x3943 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3944 = x3941 - x3943;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3945 = x3944 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3946 = Fp(x3945.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[10 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3946);
            reg = x3946;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3947 = arg2[10 * steps + ((cycle - 0) & mask)];
        assert(x3947 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3948 = x3945 - x3947;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3949 = x3948 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3950 = Fp(x3949.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[11 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3950);
            reg = x3950;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3951 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x3951 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3952 = x3949 - x3951;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3953 = x3952 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[72 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3953);
          reg = x3953;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x3954 = x5 - x3937;
        if (x3954 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3955 = x3902 - x3897;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3955 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3956 = x3903 - x3898;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3956 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3957 = x3904 - x3899;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3957 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x3958 = x3905 - x3900;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x3958 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x3959 = arg2[162 * steps + ((cycle - 0) & mask)];
      assert(x3959 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x3960 = x6 - x3959;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x3961 = x7 - x3959;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x3962 = x5 - x3959;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x3963 = x3960 * x3962;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x3964 = x3961 * x3960;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x3965 = x3961 * x3962;
      if (x3965 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[196 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x3964 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[196 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x3963 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[196 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3908);
          reg = x3908;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x3966 = arg2[161 * steps + ((cycle - 0) & mask)];
      assert(x3966 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x3967 = arg2[160 * steps + ((cycle - 0) & mask)];
      assert(x3967 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3968 = arg2[170 * steps + ((cycle - 0) & mask)];
      assert(x3968 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3969 = arg2[171 * steps + ((cycle - 0) & mask)];
      assert(x3969 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3970 = arg2[172 * steps + ((cycle - 0) & mask)];
      assert(x3970 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3971 = arg2[173 * steps + ((cycle - 0) & mask)];
      assert(x3971 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3972 = arg2[196 * steps + ((cycle - 0) & mask)];
      assert(x3972 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3973 = arg2[167 * steps + ((cycle - 0) & mask)];
        assert(x3973 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3974 = x3967 - x3973;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x3975 = (x3974 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x3976 = x7 - x3975;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[197 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3976);
          reg = x3976;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x3977 = arg2[197 * steps + ((cycle - 0) & mask)];
      assert(x3977 != Fp::invalid());
      if (x3977 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3978 = arg2[169 * steps + ((cycle - 0) & mask)];
        assert(x3978 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x3979 = x6 - x3978;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x3979 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3980 = arg2[167 * steps + ((cycle - 0) & mask)];
        assert(x3980 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3981 = x3980 - x3967;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x3982 = x3981 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3983 = Fp(x3982.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3983);
            reg = x3983;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3984 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x3984 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3985 = x3982 - x3984;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3986 = x3985 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3987 = Fp(x3986.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3987);
            reg = x3987;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3988 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x3988 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3989 = x3986 - x3988;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3990 = x3989 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x3991 = Fp(x3990.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x3991);
            reg = x3991;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x3992 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x3992 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x3993 = x3990 - x3992;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x3994 = x3993 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3994);
          reg = x3994;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x3995 = x3896 * x3972;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x3995 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x3996 = x7 - x3977;
      if (x3996 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x3997 = arg2[167 * steps + ((cycle - 0) & mask)];
        assert(x3997 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x3998 = x3967 - x3997;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x3998 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x3999 = x3966 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4000 = arg2[168 * steps + ((cycle - 0) & mask)];
        assert(x4000 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4001 = arg2[169 * steps + ((cycle - 0) & mask)];
        assert(x4001 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4002 = x4000 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4003 = x4002 + x4001;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4004 = x4003 - x3999;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4005 = x4004 + x3959;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4006 = Fp(x4005.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[12 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4006);
            reg = x4006;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4007 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x4007 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4008 = x4005 - x4007;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4009 = x4008 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4010 = Fp(x4009.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4010);
            reg = x4010;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4011 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x4011 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4012 = x4009 - x4011;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4013 = x4012 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4014 = Fp(x4013.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4014);
            reg = x4014;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4015 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x4015 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4016 = x4013 - x4015;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4017 = x4016 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[73 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4017);
          reg = x4017;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x4018 = x5 - x4001;
        if (x4018 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4019 = x3897 - x3968;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4019 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4020 = x3898 - x3969;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4020 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4021 = x3899 - x3970;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4021 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4022 = x3900 - x3971;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4022 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x4023 = arg2[169 * steps + ((cycle - 0) & mask)];
      assert(x4023 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x4024 = x6 - x4023;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x4025 = x7 - x4023;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x4026 = x5 - x4023;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x4027 = x4024 * x4026;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x4028 = x4025 * x4024;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x4029 = x4025 * x4026;
      if (x4029 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[198 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x4028 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[198 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x4027 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[198 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x3972);
          reg = x3972;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x4030 = arg2[168 * steps + ((cycle - 0) & mask)];
      assert(x4030 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x4031 = arg2[167 * steps + ((cycle - 0) & mask)];
      assert(x4031 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4032 = arg2[177 * steps + ((cycle - 0) & mask)];
      assert(x4032 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4033 = arg2[178 * steps + ((cycle - 0) & mask)];
      assert(x4033 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4034 = arg2[179 * steps + ((cycle - 0) & mask)];
      assert(x4034 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4035 = arg2[180 * steps + ((cycle - 0) & mask)];
      assert(x4035 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4036 = arg2[198 * steps + ((cycle - 0) & mask)];
      assert(x4036 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4037 = arg2[174 * steps + ((cycle - 0) & mask)];
        assert(x4037 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x4038 = x4031 - x4037;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x4039 = (x4038 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x4040 = x7 - x4039;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[199 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4040);
          reg = x4040;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4041 = arg2[199 * steps + ((cycle - 0) & mask)];
      assert(x4041 != Fp::invalid());
      if (x4041 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4042 = arg2[176 * steps + ((cycle - 0) & mask)];
        assert(x4042 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x4043 = x6 - x4042;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x4043 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4044 = arg2[174 * steps + ((cycle - 0) & mask)];
        assert(x4044 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x4045 = x4044 - x4031;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x4046 = x4045 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4047 = Fp(x4046.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4047);
            reg = x4047;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4048 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x4048 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4049 = x4046 - x4048;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4050 = x4049 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4051 = Fp(x4050.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4051);
            reg = x4051;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4052 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x4052 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4053 = x4050 - x4052;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4054 = x4053 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4055 = Fp(x4054.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4055);
            reg = x4055;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4056 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x4056 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4057 = x4054 - x4056;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4058 = x4057 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4058);
          reg = x4058;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x4059 = x3896 * x4036;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x4059 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x4060 = x7 - x4041;
      if (x4060 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4061 = arg2[174 * steps + ((cycle - 0) & mask)];
        assert(x4061 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x4062 = x4031 - x4061;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x4062 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x4063 = x4030 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4064 = arg2[175 * steps + ((cycle - 0) & mask)];
        assert(x4064 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4065 = arg2[176 * steps + ((cycle - 0) & mask)];
        assert(x4065 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4066 = x4064 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4067 = x4066 + x4065;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4068 = x4067 - x4063;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4069 = x4068 + x4023;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4070 = Fp(x4069.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4070);
            reg = x4070;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4071 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x4071 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4072 = x4069 - x4071;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4073 = x4072 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4074 = Fp(x4073.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4074);
            reg = x4074;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4075 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x4075 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4076 = x4073 - x4075;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4077 = x4076 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4078 = Fp(x4077.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4078);
            reg = x4078;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4079 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x4079 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4080 = x4077 - x4079;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4081 = x4080 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4081);
          reg = x4081;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x4082 = x5 - x4065;
        if (x4082 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4083 = x3968 - x4032;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4083 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4084 = x3969 - x4033;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4084 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4085 = x3970 - x4034;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4085 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4086 = x3971 - x4035;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4086 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x4087 = arg2[176 * steps + ((cycle - 0) & mask)];
      assert(x4087 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x4088 = x6 - x4087;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x4089 = x7 - x4087;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x4090 = x5 - x4087;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x4091 = x4088 * x4090;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x4092 = x4089 * x4088;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x4093 = x4089 * x4090;
      if (x4093 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[200 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x4092 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[200 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x4091 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[200 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4036);
          reg = x4036;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x4094 = arg2[175 * steps + ((cycle - 0) & mask)];
      assert(x4094 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x4095 = arg2[174 * steps + ((cycle - 0) & mask)];
      assert(x4095 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4096 = arg2[184 * steps + ((cycle - 0) & mask)];
      assert(x4096 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4097 = arg2[185 * steps + ((cycle - 0) & mask)];
      assert(x4097 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4098 = arg2[186 * steps + ((cycle - 0) & mask)];
      assert(x4098 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4099 = arg2[187 * steps + ((cycle - 0) & mask)];
      assert(x4099 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4100 = arg2[200 * steps + ((cycle - 0) & mask)];
      assert(x4100 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4101 = arg2[181 * steps + ((cycle - 0) & mask)];
        assert(x4101 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x4102 = x4095 - x4101;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x4103 = (x4102 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x4104 = x7 - x4103;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[201 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4104);
          reg = x4104;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4105 = arg2[201 * steps + ((cycle - 0) & mask)];
      assert(x4105 != Fp::invalid());
      if (x4105 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4106 = arg2[183 * steps + ((cycle - 0) & mask)];
        assert(x4106 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x4107 = x6 - x4106;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x4107 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4108 = arg2[181 * steps + ((cycle - 0) & mask)];
        assert(x4108 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x4109 = x4108 - x4095;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x4110 = x4109 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4111 = Fp(x4110.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4111);
            reg = x4111;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4112 = arg2[18 * steps + ((cycle - 0) & mask)];
        assert(x4112 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4113 = x4110 - x4112;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4114 = x4113 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4115 = Fp(x4114.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4115);
            reg = x4115;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4116 = arg2[19 * steps + ((cycle - 0) & mask)];
        assert(x4116 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4117 = x4114 - x4116;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4118 = x4117 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4119 = Fp(x4118.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4119);
            reg = x4119;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4120 = arg2[20 * steps + ((cycle - 0) & mask)];
        assert(x4120 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4121 = x4118 - x4120;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4122 = x4121 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4122);
          reg = x4122;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x4123 = x3896 * x4100;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x4123 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x4124 = x7 - x4105;
      if (x4124 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4125 = arg2[181 * steps + ((cycle - 0) & mask)];
        assert(x4125 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x4126 = x4095 - x4125;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x4126 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x4127 = x4094 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4128 = arg2[182 * steps + ((cycle - 0) & mask)];
        assert(x4128 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4129 = arg2[183 * steps + ((cycle - 0) & mask)];
        assert(x4129 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4130 = x4128 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4131 = x4130 + x4129;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4132 = x4131 - x4127;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4133 = x4132 + x4087;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4134 = Fp(x4133.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4134);
            reg = x4134;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4135 = arg2[18 * steps + ((cycle - 0) & mask)];
        assert(x4135 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4136 = x4133 - x4135;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4137 = x4136 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4138 = Fp(x4137.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4138);
            reg = x4138;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4139 = arg2[19 * steps + ((cycle - 0) & mask)];
        assert(x4139 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4140 = x4137 - x4139;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4141 = x4140 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4142 = Fp(x4141.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4142);
            reg = x4142;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4143 = arg2[20 * steps + ((cycle - 0) & mask)];
        assert(x4143 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4144 = x4141 - x4143;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4145 = x4144 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4145);
          reg = x4145;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x4146 = x5 - x4129;
        if (x4146 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4147 = x4032 - x4096;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4147 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4148 = x4033 - x4097;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4148 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4149 = x4034 - x4098;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4149 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4150 = x4035 - x4099;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4150 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x4151 = arg2[183 * steps + ((cycle - 0) & mask)];
      assert(x4151 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x4152 = x6 - x4151;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x4153 = x7 - x4151;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x4154 = x5 - x4151;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x4155 = x4152 * x4154;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x4156 = x4153 * x4152;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x4157 = x4153 * x4154;
      if (x4157 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[202 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x4156 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[202 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x4155 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[202 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4100);
          reg = x4100;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x4158 = arg2[182 * steps + ((cycle - 0) & mask)];
      assert(x4158 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x4159 = arg2[181 * steps + ((cycle - 0) & mask)];
      assert(x4159 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4160 = arg2[191 * steps + ((cycle - 0) & mask)];
      assert(x4160 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4161 = arg2[192 * steps + ((cycle - 0) & mask)];
      assert(x4161 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4162 = arg2[193 * steps + ((cycle - 0) & mask)];
      assert(x4162 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4163 = arg2[194 * steps + ((cycle - 0) & mask)];
      assert(x4163 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4164 = arg2[202 * steps + ((cycle - 0) & mask)];
      assert(x4164 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4165 = arg2[188 * steps + ((cycle - 0) & mask)];
        assert(x4165 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x4166 = x4159 - x4165;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x4167 = (x4166 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x4168 = x7 - x4167;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[203 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4168);
          reg = x4168;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkVerifier/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4169 = arg2[203 * steps + ((cycle - 0) & mask)];
      assert(x4169 != Fp::invalid());
      if (x4169 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4170 = arg2[190 * steps + ((cycle - 0) & mask)];
        assert(x4170 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x4171 = x6 - x4170;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x4171 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4172 = arg2[188 * steps + ((cycle - 0) & mask)];
        assert(x4172 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x4173 = x4172 - x4159;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x4174 = x4173 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4175 = Fp(x4174.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4175);
            reg = x4175;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4176 = arg2[21 * steps + ((cycle - 0) & mask)];
        assert(x4176 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4177 = x4174 - x4176;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4178 = x4177 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4179 = Fp(x4178.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4179);
            reg = x4179;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4180 = arg2[22 * steps + ((cycle - 0) & mask)];
        assert(x4180 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4181 = x4178 - x4180;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4182 = x4181 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4183 = Fp(x4182.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4183);
            reg = x4183;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4184 = arg2[23 * steps + ((cycle - 0) & mask)];
        assert(x4184 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4185 = x4182 - x4184;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4186 = x4185 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4186);
          reg = x4186;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x4187 = x3896 * x4164;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x4187 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x4188 = x7 - x4169;
      if (x4188 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4189 = arg2[188 * steps + ((cycle - 0) & mask)];
        assert(x4189 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x4190 = x4159 - x4189;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x4190 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x4191 = x4158 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4192 = arg2[189 * steps + ((cycle - 0) & mask)];
        assert(x4192 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4193 = arg2[190 * steps + ((cycle - 0) & mask)];
        assert(x4193 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4194 = x4192 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4195 = x4194 + x4193;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4196 = x4195 - x4191;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4197 = x4196 + x4151;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4198 = Fp(x4197.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4198);
            reg = x4198;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4199 = arg2[21 * steps + ((cycle - 0) & mask)];
        assert(x4199 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4200 = x4197 - x4199;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4201 = x4200 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4202 = Fp(x4201.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4202);
            reg = x4202;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4203 = arg2[22 * steps + ((cycle - 0) & mask)];
        assert(x4203 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4204 = x4201 - x4203;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4205 = x4204 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4206 = Fp(x4205.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4206);
            reg = x4206;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4207 = arg2[23 * steps + ((cycle - 0) & mask)];
        assert(x4207 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4208 = x4205 - x4207;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4209 = x4208 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4209);
          reg = x4209;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x4210 = x5 - x4193;
        if (x4210 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4211 = x4096 - x4160;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4211 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4212 = x4097 - x4161;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4212 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4213 = x4098 - x4162;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4213 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4214 = x4099 - x4163;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4214 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x4215 = arg2[190 * steps + ((cycle - 0) & mask)];
      assert(x4215 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x4216 = x6 - x4215;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x4217 = x7 - x4215;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x4218 = x5 - x4215;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x4219 = x4216 * x4218;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x4220 = x4217 * x4216;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x4221 = x4217 * x4218;
      if (x4221 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[204 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x4220 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[204 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x4219 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[204 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4164);
          reg = x4164;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
      auto x4222 = arg2[189 * steps + ((cycle - 0) & mask)];
      assert(x4222 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkElement/addr(Reg)"("zirgen/components/ram.cpp":65:40))
      auto x4223 = arg2[188 * steps + ((cycle - 0) & mask)];
      assert(x4223 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4224 = arg2[92 * steps + ((cycle - 0) & mask)];
      assert(x4224 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4225 = arg2[93 * steps + ((cycle - 0) & mask)];
      assert(x4225 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4226 = arg2[94 * steps + ((cycle - 0) & mask)];
      assert(x4226 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4227 = arg2[95 * steps + ((cycle - 0) & mask)];
      assert(x4227 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/major_mux(Mux)/big_int2(BigInt2Cycle)/RamBody/PlonkBody/RamPlonkVerifier/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4228 = arg2[204 * steps + ((cycle - 0) & mask)];
      assert(x4228 != Fp::invalid());
      {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4229 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x4229 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":85:35)
        auto x4230 = x4223 - x4229;
        // loc("zirgen/components/ram.cpp":85:35)
        auto x4231 = (x4230 == 0) ? Fp(1) : Fp(0);
        // loc("zirgen/components/ram.cpp":85:27)
        auto x4232 = x7 - x4231;
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[96 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4232);
          reg = x4232;
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4233 = arg2[96 * steps + ((cycle - 0) & mask)];
      assert(x4233 != Fp::invalid());
      if (x4233 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4234 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x4234 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":97:9)
        auto x4235 = x6 - x4234;
        // loc("zirgen/components/ram.cpp":97:9)
        assert(x4235 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4236 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x4236 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":99:17)
        auto x4237 = x4236 - x4223;
        // loc("zirgen/components/ram.cpp":99:17)
        auto x4238 = x4237 - x7;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4239 = Fp(x4238.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4239);
            reg = x4239;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4240 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x4240 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4241 = x4238 - x4240;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4242 = x4241 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4243 = Fp(x4242.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4243);
            reg = x4243;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4244 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x4244 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4245 = x4242 - x4244;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4246 = x4245 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4247 = Fp(x4246.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4247);
            reg = x4247;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4248 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x4248 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4249 = x4246 - x4248;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4250 = x4249 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4250);
          reg = x4250;
        }
        // loc("zirgen/components/ram.cpp":101:9)
        auto x4251 = x3896 * x4228;
        // loc("zirgen/components/ram.cpp":101:9)
        assert(x4251 == 0 && "eqz failed at: zirgen/components/ram.cpp:101");
      }
      // loc("zirgen/components/ram.cpp":105:19)
      auto x4252 = x7 - x4233;
      if (x4252 != 0) {
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4253 = arg2[89 * steps + ((cycle - 0) & mask)];
        assert(x4253 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":107:9)
        auto x4254 = x4223 - x4253;
        // loc("zirgen/components/ram.cpp":107:9)
        assert(x4254 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
        // loc("zirgen/components/ram.cpp":109:43)
        auto x4255 = x4222 * x2;
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4256 = arg2[90 * steps + ((cycle - 0) & mask)];
        assert(x4256 != Fp::invalid());
        // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
        auto x4257 = arg2[91 * steps + ((cycle - 0) & mask)];
        assert(x4257 != Fp::invalid());
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4258 = x4256 * x2;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4259 = x4258 + x4257;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4260 = x4259 - x4255;
        // loc("zirgen/components/ram.cpp":109:17)
        auto x4261 = x4260 + x4215;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4262 = Fp(x4261.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[3 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4262);
            reg = x4262;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4263 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x4263 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4264 = x4261 - x4263;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4265 = x4264 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4266 = Fp(x4265.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[4 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4266);
            reg = x4266;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4267 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x4267 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4268 = x4265 - x4267;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4269 = x4268 * x3;
        {
          // loc("zirgen/components/bytes.cpp":106:21)
          auto x4270 = Fp(x4269.asUInt32() & x4.asUInt32());
          // loc("zirgen/components/bytes.cpp":106:12)
          {
            auto& reg = arg2[5 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x4270);
            reg = x4270;
          }
        }
        // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
        auto x4271 = arg2[5 * steps + ((cycle - 0) & mask)];
        assert(x4271 != Fp::invalid());
        // loc("zirgen/components/bytes.cpp":107:11)
        auto x4272 = x4269 - x4271;
        // loc("zirgen/components/bytes.cpp":107:10)
        auto x4273 = x4272 * x3;
        // loc("./zirgen/components/bits.h":78:23)
        {
          auto& reg = arg2[69 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4273);
          reg = x4273;
        }
        // loc("zirgen/components/ram.cpp":111:39)
        auto x4274 = x5 - x4257;
        if (x4274 != 0) {
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4275 = x4160 - x4224;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4275 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4276 = x4161 - x4225;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4276 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4277 = x4162 - x4226;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4277 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
          // loc("zirgen/components/ram.cpp":111:43)
          auto x4278 = x4163 - x4227;
          // loc("zirgen/components/ram.cpp":111:43)
          assert(x4278 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        }
      }
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x4279 = arg2[91 * steps + ((cycle - 0) & mask)];
      assert(x4279 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":115:17)
      auto x4280 = x6 - x4279;
      // loc("zirgen/components/ram.cpp":114:18)
      auto x4281 = x7 - x4279;
      // loc("zirgen/components/ram.cpp":115:54)
      auto x4282 = x5 - x4279;
      // loc("zirgen/components/ram.cpp":115:16)
      auto x4283 = x4280 * x4282;
      // loc("zirgen/components/ram.cpp":114:17)
      auto x4284 = x4281 * x4280;
      // loc("zirgen/components/ram.cpp":116:18)
      auto x4285 = x4281 * x4282;
      if (x4285 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6);
          reg = x6;
        }
      }
      if (x4284 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7);
          reg = x7;
        }
      }
      if (x4283 != 0) {
        // loc("./zirgen/components/bits.h":37:23)
        {
          auto& reg = arg2[97 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4228);
          reg = x4228;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x4286 = arg2[117 * steps + ((cycle - 0) & mask)];
    assert(x4286 != Fp::invalid());
    if (x4286 != 0) {
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4287 = arg2[89 * steps + ((cycle - 1) & mask)];
      assert(x4287 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4288 = arg2[90 * steps + ((cycle - 1) & mask)];
      assert(x4288 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4289 = arg2[91 * steps + ((cycle - 1) & mask)];
      assert(x4289 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4290 = arg2[92 * steps + ((cycle - 1) & mask)];
      assert(x4290 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4291 = arg2[93 * steps + ((cycle - 1) & mask)];
      assert(x4291 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4292 = arg2[94 * steps + ((cycle - 1) & mask)];
      assert(x4292 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4293 = arg2[95 * steps + ((cycle - 1) & mask)];
      assert(x4293 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":46:3)
      {
        auto& reg = arg2[89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4287);
        reg = x4287;
      }
      // loc("zirgen/components/ram.cpp":47:3)
      {
        auto& reg = arg2[90 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4288);
        reg = x4288;
      }
      // loc("zirgen/components/ram.cpp":48:3)
      {
        auto& reg = arg2[91 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4289);
        reg = x4289;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[92 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4290);
        reg = x4290;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[93 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4291);
        reg = x4291;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[94 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4292);
        reg = x4292;
      }
      // loc("zirgen/components/u32.cpp":98:5)
      {
        auto& reg = arg2[95 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4293);
        reg = x4293;
      }
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":102:10))
      auto x4294 = arg2[3 * steps + ((cycle - 1) & mask)];
      assert(x4294 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":102:10))
      auto x4295 = arg2[4 * steps + ((cycle - 1) & mask)];
      assert(x4295 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":102:10))
      auto x4296 = arg2[5 * steps + ((cycle - 1) & mask)];
      assert(x4296 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/extra(Twit)/twit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4297 = arg2[69 * steps + ((cycle - 1) & mask)];
      assert(x4297 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4298 = arg2[96 * steps + ((cycle - 1) & mask)];
      assert(x4298 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4299 = arg2[97 * steps + ((cycle - 1) & mask)];
      assert(x4299 != Fp::invalid());
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[96 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4298);
        reg = x4298;
      }
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[97 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4299);
        reg = x4299;
      }
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x4300 = Fp(x4294.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4300);
          reg = x4300;
        }
      }
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x4301 = Fp(x4295.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4301);
          reg = x4301;
        }
      }
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x4302 = Fp(x4296.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4302);
          reg = x4302;
        }
      }
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4297);
        reg = x4297;
      }
    }
  }
  if (x12 != 0) {
    // loc("zirgen/components/ram.cpp":32:3)
    {
      auto& reg = arg2[98 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x1);
      reg = x1;
    }
    // loc("zirgen/components/ram.cpp":33:3)
    {
      auto& reg = arg2[99 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x0);
      reg = x0;
    }
    // loc("zirgen/components/ram.cpp":34:3)
    {
      auto& reg = arg2[100 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("zirgen/components/u32.cpp":38:5)
    {
      auto& reg = arg2[101 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("zirgen/components/u32.cpp":38:5)
    {
      auto& reg = arg2[102 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("zirgen/components/u32.cpp":38:5)
    {
      auto& reg = arg2[103 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("zirgen/components/u32.cpp":38:5)
    {
      auto& reg = arg2[104 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/PlonkFini/RamPlonkElement/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x4303 = arg2[101 * steps + ((cycle - 0) & mask)];
    assert(x4303 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/PlonkFini/RamPlonkElement/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x4304 = arg2[102 * steps + ((cycle - 0) & mask)];
    assert(x4304 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/PlonkFini/RamPlonkElement/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x4305 = arg2[103 * steps + ((cycle - 0) & mask)];
    assert(x4305 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/PlonkFini/RamPlonkElement/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x4306 = arg2[104 * steps + ((cycle - 0) & mask)];
    assert(x4306 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/header(RamHeader)/element(RamPlonkElement)/cycle(Reg)"("zirgen/components/ram.cpp":66:42))
    auto x4307 = arg2[90 * steps + ((cycle - 1) & mask)];
    assert(x4307 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[0](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x4308 = arg2[92 * steps + ((cycle - 1) & mask)];
    assert(x4308 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[1](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x4309 = arg2[93 * steps + ((cycle - 1) & mask)];
    assert(x4309 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[2](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x4310 = arg2[94 * steps + ((cycle - 1) & mask)];
    assert(x4310 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/header(RamHeader)/element(RamPlonkElement)/data(U32Reg)/byte[3](Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x4311 = arg2[95 * steps + ((cycle - 1) & mask)];
    assert(x4311 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/header(RamHeader)/element(RamPlonkElement)/addr(Reg)"("zirgen/components/ram.cpp":65:40))
    auto x4312 = arg2[89 * steps + ((cycle - 1) & mask)];
    assert(x4312 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/header(RamHeader)/element(RamPlonkElement)/mem_op(Reg)"("zirgen/components/ram.cpp":67:42))
    auto x4313 = arg2[91 * steps + ((cycle - 1) & mask)];
    assert(x4313 != Fp::invalid());
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/header(RamHeader)/verifier(RamPlonkVerifier)/dirty(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x4314 = arg2[97 * steps + ((cycle - 1) & mask)];
    assert(x4314 != Fp::invalid());
    {
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/PlonkFini/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x4315 = arg2[98 * steps + ((cycle - 0) & mask)];
      assert(x4315 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":85:35)
      auto x4316 = x4312 - x4315;
      // loc("zirgen/components/ram.cpp":85:35)
      auto x4317 = (x4316 == 0) ? Fp(1) : Fp(0);
      // loc("zirgen/components/ram.cpp":85:27)
      auto x4318 = x7 - x4317;
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[96 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4318);
        reg = x4318;
      }
    }
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/header(RamHeader)/verifier(RamPlonkVerifier)/is_new_addr(Bit)/bit(Reg)"("./zirgen/compiler/edsl/component.h":164:27))
    auto x4319 = arg2[96 * steps + ((cycle - 0) & mask)];
    assert(x4319 != Fp::invalid());
    if (x4319 != 0) {
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/PlonkFini/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x4320 = arg2[100 * steps + ((cycle - 0) & mask)];
      assert(x4320 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":97:9)
      auto x4321 = x6 - x4320;
      // loc("zirgen/components/ram.cpp":97:9)
      assert(x4321 == 0 && "eqz failed at: zirgen/components/ram.cpp:97");
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/PlonkFini/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x4322 = arg2[98 * steps + ((cycle - 0) & mask)];
      assert(x4322 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":99:17)
      auto x4323 = x4322 - x4312;
      // loc("zirgen/components/ram.cpp":99:17)
      auto x4324 = x4323 - x7;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x4325 = Fp(x4324.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4325);
          reg = x4325;
        }
      }
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x4326 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x4326 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x4327 = x4324 - x4326;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x4328 = x4327 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x4329 = Fp(x4328.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4329);
          reg = x4329;
        }
      }
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x4330 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x4330 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x4331 = x4328 - x4330;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x4332 = x4331 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x4333 = Fp(x4332.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4333);
          reg = x4333;
        }
      }
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x4334 = arg2[5 * steps + ((cycle - 0) & mask)];
      assert(x4334 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x4335 = x4332 - x4334;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x4336 = x4335 * x3;
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4336);
        reg = x4336;
      }
    }
    // loc("zirgen/components/ram.cpp":105:19)
    auto x4337 = x7 - x4319;
    if (x4337 != 0) {
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/PlonkFini/RamPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x4338 = arg2[98 * steps + ((cycle - 0) & mask)];
      assert(x4338 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":107:9)
      auto x4339 = x4312 - x4338;
      // loc("zirgen/components/ram.cpp":107:9)
      assert(x4339 == 0 && "eqz failed at: zirgen/components/ram.cpp:107");
      // loc("zirgen/components/ram.cpp":109:43)
      auto x4340 = x4307 * x2;
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/PlonkFini/RamPlonkElement/cycle(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x4341 = arg2[99 * steps + ((cycle - 0) & mask)];
      assert(x4341 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/PlonkFini/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x4342 = arg2[100 * steps + ((cycle - 0) & mask)];
      assert(x4342 != Fp::invalid());
      // loc("zirgen/components/ram.cpp":109:17)
      auto x4343 = x4341 * x2;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x4344 = x4343 + x4342;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x4345 = x4344 - x4340;
      // loc("zirgen/components/ram.cpp":109:17)
      auto x4346 = x4345 + x4313;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x4347 = Fp(x4346.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4347);
          reg = x4347;
        }
      }
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x4348 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x4348 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x4349 = x4346 - x4348;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x4350 = x4349 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x4351 = Fp(x4350.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4351);
          reg = x4351;
        }
      }
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x4352 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x4352 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x4353 = x4350 - x4352;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x4354 = x4353 * x3;
      {
        // loc("zirgen/components/bytes.cpp":106:21)
        auto x4355 = Fp(x4354.asUInt32() & x4.asUInt32());
        // loc("zirgen/components/bytes.cpp":106:12)
        {
          auto& reg = arg2[5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x4355);
          reg = x4355;
        }
      }
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("zirgen/components/bytes.cpp":107:16))
      auto x4356 = arg2[5 * steps + ((cycle - 0) & mask)];
      assert(x4356 != Fp::invalid());
      // loc("zirgen/components/bytes.cpp":107:11)
      auto x4357 = x4354 - x4356;
      // loc("zirgen/components/bytes.cpp":107:10)
      auto x4358 = x4357 * x3;
      // loc("./zirgen/components/bits.h":78:23)
      {
        auto& reg = arg2[69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4358);
        reg = x4358;
      }
      // loc("zirgen/components/ram.cpp":111:39)
      auto x4359 = x5 - x4342;
      if (x4359 != 0) {
        // loc("zirgen/components/ram.cpp":111:43)
        auto x4360 = x4308 - x4303;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x4360 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x4361 = x4309 - x4304;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x4361 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x4362 = x4310 - x4305;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x4362 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
        // loc("zirgen/components/ram.cpp":111:43)
        auto x4363 = x4311 - x4306;
        // loc("zirgen/components/ram.cpp":111:43)
        assert(x4363 == 0 && "eqz failed at: zirgen/components/ram.cpp:111");
      }
    }
    // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/PlonkFini/RamPlonkElement/mem_op(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x4364 = arg2[100 * steps + ((cycle - 0) & mask)];
    assert(x4364 != Fp::invalid());
    // loc("zirgen/components/ram.cpp":115:17)
    auto x4365 = x6 - x4364;
    // loc("zirgen/components/ram.cpp":114:18)
    auto x4366 = x7 - x4364;
    // loc("zirgen/components/ram.cpp":115:54)
    auto x4367 = x5 - x4364;
    // loc("zirgen/components/ram.cpp":115:16)
    auto x4368 = x4365 * x4367;
    // loc("zirgen/components/ram.cpp":114:17)
    auto x4369 = x4366 * x4365;
    // loc("zirgen/components/ram.cpp":116:18)
    auto x4370 = x4366 * x4367;
    if (x4370 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[97 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x6);
        reg = x6;
      }
    }
    if (x4369 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[97 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x7);
        reg = x7;
      }
    }
    if (x4368 != 0) {
      // loc("./zirgen/components/bits.h":37:23)
      {
        auto& reg = arg2[97 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4314);
        reg = x4314;
      }
    }
  }
  if (x8 != 0) {
    {
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4371 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x4371 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4372 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x4372 != Fp::invalid());
      extern_args[0] = x4371;
      extern_args[1] = x4372;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4373 = arg2[5 * steps + ((cycle - 0) & mask)];
      assert(x4373 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4374 = arg2[6 * steps + ((cycle - 0) & mask)];
      assert(x4374 != Fp::invalid());
      extern_args[0] = x4373;
      extern_args[1] = x4374;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4375 = arg2[7 * steps + ((cycle - 0) & mask)];
      assert(x4375 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4376 = arg2[8 * steps + ((cycle - 0) & mask)];
      assert(x4376 != Fp::invalid());
      extern_args[0] = x4375;
      extern_args[1] = x4376;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4377 = arg2[9 * steps + ((cycle - 0) & mask)];
      assert(x4377 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4378 = arg2[10 * steps + ((cycle - 0) & mask)];
      assert(x4378 != Fp::invalid());
      extern_args[0] = x4377;
      extern_args[1] = x4378;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4379 = arg2[11 * steps + ((cycle - 0) & mask)];
      assert(x4379 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4380 = arg2[12 * steps + ((cycle - 0) & mask)];
      assert(x4380 != Fp::invalid());
      extern_args[0] = x4379;
      extern_args[1] = x4380;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4381 = arg2[13 * steps + ((cycle - 0) & mask)];
      assert(x4381 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4382 = arg2[14 * steps + ((cycle - 0) & mask)];
      assert(x4382 != Fp::invalid());
      extern_args[0] = x4381;
      extern_args[1] = x4382;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4383 = arg2[15 * steps + ((cycle - 0) & mask)];
      assert(x4383 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4384 = arg2[16 * steps + ((cycle - 0) & mask)];
      assert(x4384 != Fp::invalid());
      extern_args[0] = x4383;
      extern_args[1] = x4384;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4385 = arg2[17 * steps + ((cycle - 0) & mask)];
      assert(x4385 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4386 = arg2[18 * steps + ((cycle - 0) & mask)];
      assert(x4386 != Fp::invalid());
      extern_args[0] = x4385;
      extern_args[1] = x4386;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4387 = arg2[19 * steps + ((cycle - 0) & mask)];
      assert(x4387 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4388 = arg2[20 * steps + ((cycle - 0) & mask)];
      assert(x4388 != Fp::invalid());
      extern_args[0] = x4387;
      extern_args[1] = x4388;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4389 = arg2[21 * steps + ((cycle - 0) & mask)];
      assert(x4389 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4390 = arg2[22 * steps + ((cycle - 0) & mask)];
      assert(x4390 != Fp::invalid());
      extern_args[0] = x4389;
      extern_args[1] = x4390;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4391 = arg2[23 * steps + ((cycle - 0) & mask)];
      assert(x4391 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4392 = arg2[24 * steps + ((cycle - 0) & mask)];
      assert(x4392 != Fp::invalid());
      extern_args[0] = x4391;
      extern_args[1] = x4392;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4393 = arg2[25 * steps + ((cycle - 0) & mask)];
      assert(x4393 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4394 = arg2[26 * steps + ((cycle - 0) & mask)];
      assert(x4394 != Fp::invalid());
      extern_args[0] = x4393;
      extern_args[1] = x4394;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4395 = arg2[27 * steps + ((cycle - 0) & mask)];
      assert(x4395 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4396 = arg2[28 * steps + ((cycle - 0) & mask)];
      assert(x4396 != Fp::invalid());
      extern_args[0] = x4395;
      extern_args[1] = x4396;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4397 = arg2[29 * steps + ((cycle - 0) & mask)];
      assert(x4397 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4398 = arg2[30 * steps + ((cycle - 0) & mask)];
      assert(x4398 != Fp::invalid());
      extern_args[0] = x4397;
      extern_args[1] = x4398;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4399 = arg2[31 * steps + ((cycle - 0) & mask)];
      assert(x4399 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4400 = arg2[32 * steps + ((cycle - 0) & mask)];
      assert(x4400 != Fp::invalid());
      extern_args[0] = x4399;
      extern_args[1] = x4400;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4401 = arg2[33 * steps + ((cycle - 0) & mask)];
      assert(x4401 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4402 = arg2[34 * steps + ((cycle - 0) & mask)];
      assert(x4402 != Fp::invalid());
      extern_args[0] = x4401;
      extern_args[1] = x4402;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4403 = arg2[35 * steps + ((cycle - 0) & mask)];
      assert(x4403 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4404 = arg2[36 * steps + ((cycle - 0) & mask)];
      assert(x4404 != Fp::invalid());
      extern_args[0] = x4403;
      extern_args[1] = x4404;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4405 = arg2[37 * steps + ((cycle - 0) & mask)];
      assert(x4405 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4406 = arg2[38 * steps + ((cycle - 0) & mask)];
      assert(x4406 != Fp::invalid());
      extern_args[0] = x4405;
      extern_args[1] = x4406;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4407 = arg2[39 * steps + ((cycle - 0) & mask)];
      assert(x4407 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4408 = arg2[40 * steps + ((cycle - 0) & mask)];
      assert(x4408 != Fp::invalid());
      extern_args[0] = x4407;
      extern_args[1] = x4408;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4409 = arg2[41 * steps + ((cycle - 0) & mask)];
      assert(x4409 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4410 = arg2[42 * steps + ((cycle - 0) & mask)];
      assert(x4410 != Fp::invalid());
      extern_args[0] = x4409;
      extern_args[1] = x4410;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4411 = arg2[43 * steps + ((cycle - 0) & mask)];
      assert(x4411 != Fp::invalid());
      // loc("Top/mux(Mux)/bytes_setup(BytesSetupStep)/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4412 = arg2[44 * steps + ((cycle - 0) & mask)];
      assert(x4412 != Fp::invalid());
      extern_args[0] = x4411;
      extern_args[1] = x4412;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
    }
  }
  if (x13 != 0) {
    {
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4413 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x4413 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4414 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x4414 != Fp::invalid());
      extern_args[0] = x4413;
      extern_args[1] = x4414;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4415 = arg2[5 * steps + ((cycle - 0) & mask)];
      assert(x4415 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4416 = arg2[6 * steps + ((cycle - 0) & mask)];
      assert(x4416 != Fp::invalid());
      extern_args[0] = x4415;
      extern_args[1] = x4416;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4417 = arg2[7 * steps + ((cycle - 0) & mask)];
      assert(x4417 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4418 = arg2[8 * steps + ((cycle - 0) & mask)];
      assert(x4418 != Fp::invalid());
      extern_args[0] = x4417;
      extern_args[1] = x4418;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4419 = arg2[9 * steps + ((cycle - 0) & mask)];
      assert(x4419 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4420 = arg2[10 * steps + ((cycle - 0) & mask)];
      assert(x4420 != Fp::invalid());
      extern_args[0] = x4419;
      extern_args[1] = x4420;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4421 = arg2[11 * steps + ((cycle - 0) & mask)];
      assert(x4421 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4422 = arg2[12 * steps + ((cycle - 0) & mask)];
      assert(x4422 != Fp::invalid());
      extern_args[0] = x4421;
      extern_args[1] = x4422;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4423 = arg2[13 * steps + ((cycle - 0) & mask)];
      assert(x4423 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4424 = arg2[14 * steps + ((cycle - 0) & mask)];
      assert(x4424 != Fp::invalid());
      extern_args[0] = x4423;
      extern_args[1] = x4424;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4425 = arg2[15 * steps + ((cycle - 0) & mask)];
      assert(x4425 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4426 = arg2[16 * steps + ((cycle - 0) & mask)];
      assert(x4426 != Fp::invalid());
      extern_args[0] = x4425;
      extern_args[1] = x4426;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4427 = arg2[17 * steps + ((cycle - 0) & mask)];
      assert(x4427 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4428 = arg2[18 * steps + ((cycle - 0) & mask)];
      assert(x4428 != Fp::invalid());
      extern_args[0] = x4427;
      extern_args[1] = x4428;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4429 = arg2[19 * steps + ((cycle - 0) & mask)];
      assert(x4429 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4430 = arg2[20 * steps + ((cycle - 0) & mask)];
      assert(x4430 != Fp::invalid());
      extern_args[0] = x4429;
      extern_args[1] = x4430;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4431 = arg2[21 * steps + ((cycle - 0) & mask)];
      assert(x4431 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4432 = arg2[22 * steps + ((cycle - 0) & mask)];
      assert(x4432 != Fp::invalid());
      extern_args[0] = x4431;
      extern_args[1] = x4432;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4433 = arg2[23 * steps + ((cycle - 0) & mask)];
      assert(x4433 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4434 = arg2[24 * steps + ((cycle - 0) & mask)];
      assert(x4434 != Fp::invalid());
      extern_args[0] = x4433;
      extern_args[1] = x4434;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4435 = arg2[25 * steps + ((cycle - 0) & mask)];
      assert(x4435 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4436 = arg2[26 * steps + ((cycle - 0) & mask)];
      assert(x4436 != Fp::invalid());
      extern_args[0] = x4435;
      extern_args[1] = x4436;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4437 = arg2[27 * steps + ((cycle - 0) & mask)];
      assert(x4437 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4438 = arg2[28 * steps + ((cycle - 0) & mask)];
      assert(x4438 != Fp::invalid());
      extern_args[0] = x4437;
      extern_args[1] = x4438;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4439 = arg2[29 * steps + ((cycle - 0) & mask)];
      assert(x4439 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4440 = arg2[30 * steps + ((cycle - 0) & mask)];
      assert(x4440 != Fp::invalid());
      extern_args[0] = x4439;
      extern_args[1] = x4440;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4441 = arg2[31 * steps + ((cycle - 0) & mask)];
      assert(x4441 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4442 = arg2[32 * steps + ((cycle - 0) & mask)];
      assert(x4442 != Fp::invalid());
      extern_args[0] = x4441;
      extern_args[1] = x4442;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4443 = arg2[33 * steps + ((cycle - 0) & mask)];
      assert(x4443 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4444 = arg2[34 * steps + ((cycle - 0) & mask)];
      assert(x4444 != Fp::invalid());
      extern_args[0] = x4443;
      extern_args[1] = x4444;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4445 = arg2[35 * steps + ((cycle - 0) & mask)];
      assert(x4445 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_init(RamInitStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4446 = arg2[36 * steps + ((cycle - 0) & mask)];
      assert(x4446 != Fp::invalid());
      extern_args[0] = x4445;
      extern_args[1] = x4446;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
    }
  }
  if (x9 != 0) {
    {
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4447 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x4447 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4448 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x4448 != Fp::invalid());
      extern_args[0] = x4447;
      extern_args[1] = x4448;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4449 = arg2[5 * steps + ((cycle - 0) & mask)];
      assert(x4449 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4450 = arg2[6 * steps + ((cycle - 0) & mask)];
      assert(x4450 != Fp::invalid());
      extern_args[0] = x4449;
      extern_args[1] = x4450;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4451 = arg2[7 * steps + ((cycle - 0) & mask)];
      assert(x4451 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4452 = arg2[8 * steps + ((cycle - 0) & mask)];
      assert(x4452 != Fp::invalid());
      extern_args[0] = x4451;
      extern_args[1] = x4452;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4453 = arg2[9 * steps + ((cycle - 0) & mask)];
      assert(x4453 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4454 = arg2[10 * steps + ((cycle - 0) & mask)];
      assert(x4454 != Fp::invalid());
      extern_args[0] = x4453;
      extern_args[1] = x4454;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4455 = arg2[11 * steps + ((cycle - 0) & mask)];
      assert(x4455 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4456 = arg2[12 * steps + ((cycle - 0) & mask)];
      assert(x4456 != Fp::invalid());
      extern_args[0] = x4455;
      extern_args[1] = x4456;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4457 = arg2[13 * steps + ((cycle - 0) & mask)];
      assert(x4457 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4458 = arg2[14 * steps + ((cycle - 0) & mask)];
      assert(x4458 != Fp::invalid());
      extern_args[0] = x4457;
      extern_args[1] = x4458;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4459 = arg2[15 * steps + ((cycle - 0) & mask)];
      assert(x4459 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4460 = arg2[16 * steps + ((cycle - 0) & mask)];
      assert(x4460 != Fp::invalid());
      extern_args[0] = x4459;
      extern_args[1] = x4460;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4461 = arg2[17 * steps + ((cycle - 0) & mask)];
      assert(x4461 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4462 = arg2[18 * steps + ((cycle - 0) & mask)];
      assert(x4462 != Fp::invalid());
      extern_args[0] = x4461;
      extern_args[1] = x4462;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4463 = arg2[19 * steps + ((cycle - 0) & mask)];
      assert(x4463 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4464 = arg2[20 * steps + ((cycle - 0) & mask)];
      assert(x4464 != Fp::invalid());
      extern_args[0] = x4463;
      extern_args[1] = x4464;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4465 = arg2[21 * steps + ((cycle - 0) & mask)];
      assert(x4465 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4466 = arg2[22 * steps + ((cycle - 0) & mask)];
      assert(x4466 != Fp::invalid());
      extern_args[0] = x4465;
      extern_args[1] = x4466;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4467 = arg2[23 * steps + ((cycle - 0) & mask)];
      assert(x4467 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4468 = arg2[24 * steps + ((cycle - 0) & mask)];
      assert(x4468 != Fp::invalid());
      extern_args[0] = x4467;
      extern_args[1] = x4468;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4469 = arg2[25 * steps + ((cycle - 0) & mask)];
      assert(x4469 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4470 = arg2[26 * steps + ((cycle - 0) & mask)];
      assert(x4470 != Fp::invalid());
      extern_args[0] = x4469;
      extern_args[1] = x4470;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4471 = arg2[27 * steps + ((cycle - 0) & mask)];
      assert(x4471 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4472 = arg2[28 * steps + ((cycle - 0) & mask)];
      assert(x4472 != Fp::invalid());
      extern_args[0] = x4471;
      extern_args[1] = x4472;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4473 = arg2[29 * steps + ((cycle - 0) & mask)];
      assert(x4473 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4474 = arg2[30 * steps + ((cycle - 0) & mask)];
      assert(x4474 != Fp::invalid());
      extern_args[0] = x4473;
      extern_args[1] = x4474;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4475 = arg2[31 * steps + ((cycle - 0) & mask)];
      assert(x4475 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4476 = arg2[32 * steps + ((cycle - 0) & mask)];
      assert(x4476 != Fp::invalid());
      extern_args[0] = x4475;
      extern_args[1] = x4476;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4477 = arg2[33 * steps + ((cycle - 0) & mask)];
      assert(x4477 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4478 = arg2[34 * steps + ((cycle - 0) & mask)];
      assert(x4478 != Fp::invalid());
      extern_args[0] = x4477;
      extern_args[1] = x4478;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4479 = arg2[35 * steps + ((cycle - 0) & mask)];
      assert(x4479 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_load(RamLoadStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4480 = arg2[36 * steps + ((cycle - 0) & mask)];
      assert(x4480 != Fp::invalid());
      extern_args[0] = x4479;
      extern_args[1] = x4480;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
    }
  }
  if (x10 != 0) {
    {
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4481 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x4481 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4482 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x4482 != Fp::invalid());
      extern_args[0] = x4481;
      extern_args[1] = x4482;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4483 = arg2[5 * steps + ((cycle - 0) & mask)];
      assert(x4483 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4484 = arg2[6 * steps + ((cycle - 0) & mask)];
      assert(x4484 != Fp::invalid());
      extern_args[0] = x4483;
      extern_args[1] = x4484;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4485 = arg2[7 * steps + ((cycle - 0) & mask)];
      assert(x4485 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4486 = arg2[8 * steps + ((cycle - 0) & mask)];
      assert(x4486 != Fp::invalid());
      extern_args[0] = x4485;
      extern_args[1] = x4486;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4487 = arg2[9 * steps + ((cycle - 0) & mask)];
      assert(x4487 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4488 = arg2[10 * steps + ((cycle - 0) & mask)];
      assert(x4488 != Fp::invalid());
      extern_args[0] = x4487;
      extern_args[1] = x4488;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4489 = arg2[11 * steps + ((cycle - 0) & mask)];
      assert(x4489 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4490 = arg2[12 * steps + ((cycle - 0) & mask)];
      assert(x4490 != Fp::invalid());
      extern_args[0] = x4489;
      extern_args[1] = x4490;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4491 = arg2[13 * steps + ((cycle - 0) & mask)];
      assert(x4491 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4492 = arg2[14 * steps + ((cycle - 0) & mask)];
      assert(x4492 != Fp::invalid());
      extern_args[0] = x4491;
      extern_args[1] = x4492;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4493 = arg2[15 * steps + ((cycle - 0) & mask)];
      assert(x4493 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4494 = arg2[16 * steps + ((cycle - 0) & mask)];
      assert(x4494 != Fp::invalid());
      extern_args[0] = x4493;
      extern_args[1] = x4494;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4495 = arg2[17 * steps + ((cycle - 0) & mask)];
      assert(x4495 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4496 = arg2[18 * steps + ((cycle - 0) & mask)];
      assert(x4496 != Fp::invalid());
      extern_args[0] = x4495;
      extern_args[1] = x4496;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4497 = arg2[19 * steps + ((cycle - 0) & mask)];
      assert(x4497 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4498 = arg2[20 * steps + ((cycle - 0) & mask)];
      assert(x4498 != Fp::invalid());
      extern_args[0] = x4497;
      extern_args[1] = x4498;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4499 = arg2[21 * steps + ((cycle - 0) & mask)];
      assert(x4499 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4500 = arg2[22 * steps + ((cycle - 0) & mask)];
      assert(x4500 != Fp::invalid());
      extern_args[0] = x4499;
      extern_args[1] = x4500;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4501 = arg2[23 * steps + ((cycle - 0) & mask)];
      assert(x4501 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4502 = arg2[24 * steps + ((cycle - 0) & mask)];
      assert(x4502 != Fp::invalid());
      extern_args[0] = x4501;
      extern_args[1] = x4502;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4503 = arg2[25 * steps + ((cycle - 0) & mask)];
      assert(x4503 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4504 = arg2[26 * steps + ((cycle - 0) & mask)];
      assert(x4504 != Fp::invalid());
      extern_args[0] = x4503;
      extern_args[1] = x4504;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4505 = arg2[27 * steps + ((cycle - 0) & mask)];
      assert(x4505 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4506 = arg2[28 * steps + ((cycle - 0) & mask)];
      assert(x4506 != Fp::invalid());
      extern_args[0] = x4505;
      extern_args[1] = x4506;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4507 = arg2[29 * steps + ((cycle - 0) & mask)];
      assert(x4507 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4508 = arg2[30 * steps + ((cycle - 0) & mask)];
      assert(x4508 != Fp::invalid());
      extern_args[0] = x4507;
      extern_args[1] = x4508;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4509 = arg2[31 * steps + ((cycle - 0) & mask)];
      assert(x4509 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4510 = arg2[32 * steps + ((cycle - 0) & mask)];
      assert(x4510 != Fp::invalid());
      extern_args[0] = x4509;
      extern_args[1] = x4510;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4511 = arg2[33 * steps + ((cycle - 0) & mask)];
      assert(x4511 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4512 = arg2[34 * steps + ((cycle - 0) & mask)];
      assert(x4512 != Fp::invalid());
      extern_args[0] = x4511;
      extern_args[1] = x4512;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4513 = arg2[35 * steps + ((cycle - 0) & mask)];
      assert(x4513 != Fp::invalid());
      // loc("Top/mux(Mux)/reset(ResetStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4514 = arg2[36 * steps + ((cycle - 0) & mask)];
      assert(x4514 != Fp::invalid());
      extern_args[0] = x4513;
      extern_args[1] = x4514;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
    }
  }
  if (x11 != 0) {
    {
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4515 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x4515 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4516 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x4516 != Fp::invalid());
      extern_args[0] = x4515;
      extern_args[1] = x4516;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4517 = arg2[5 * steps + ((cycle - 0) & mask)];
      assert(x4517 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4518 = arg2[6 * steps + ((cycle - 0) & mask)];
      assert(x4518 != Fp::invalid());
      extern_args[0] = x4517;
      extern_args[1] = x4518;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4519 = arg2[7 * steps + ((cycle - 0) & mask)];
      assert(x4519 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4520 = arg2[8 * steps + ((cycle - 0) & mask)];
      assert(x4520 != Fp::invalid());
      extern_args[0] = x4519;
      extern_args[1] = x4520;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4521 = arg2[9 * steps + ((cycle - 0) & mask)];
      assert(x4521 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4522 = arg2[10 * steps + ((cycle - 0) & mask)];
      assert(x4522 != Fp::invalid());
      extern_args[0] = x4521;
      extern_args[1] = x4522;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4523 = arg2[11 * steps + ((cycle - 0) & mask)];
      assert(x4523 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4524 = arg2[12 * steps + ((cycle - 0) & mask)];
      assert(x4524 != Fp::invalid());
      extern_args[0] = x4523;
      extern_args[1] = x4524;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4525 = arg2[13 * steps + ((cycle - 0) & mask)];
      assert(x4525 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4526 = arg2[14 * steps + ((cycle - 0) & mask)];
      assert(x4526 != Fp::invalid());
      extern_args[0] = x4525;
      extern_args[1] = x4526;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4527 = arg2[15 * steps + ((cycle - 0) & mask)];
      assert(x4527 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4528 = arg2[16 * steps + ((cycle - 0) & mask)];
      assert(x4528 != Fp::invalid());
      extern_args[0] = x4527;
      extern_args[1] = x4528;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4529 = arg2[17 * steps + ((cycle - 0) & mask)];
      assert(x4529 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4530 = arg2[18 * steps + ((cycle - 0) & mask)];
      assert(x4530 != Fp::invalid());
      extern_args[0] = x4529;
      extern_args[1] = x4530;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4531 = arg2[19 * steps + ((cycle - 0) & mask)];
      assert(x4531 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4532 = arg2[20 * steps + ((cycle - 0) & mask)];
      assert(x4532 != Fp::invalid());
      extern_args[0] = x4531;
      extern_args[1] = x4532;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4533 = arg2[21 * steps + ((cycle - 0) & mask)];
      assert(x4533 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4534 = arg2[22 * steps + ((cycle - 0) & mask)];
      assert(x4534 != Fp::invalid());
      extern_args[0] = x4533;
      extern_args[1] = x4534;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4535 = arg2[23 * steps + ((cycle - 0) & mask)];
      assert(x4535 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4536 = arg2[24 * steps + ((cycle - 0) & mask)];
      assert(x4536 != Fp::invalid());
      extern_args[0] = x4535;
      extern_args[1] = x4536;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4537 = arg2[25 * steps + ((cycle - 0) & mask)];
      assert(x4537 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4538 = arg2[26 * steps + ((cycle - 0) & mask)];
      assert(x4538 != Fp::invalid());
      extern_args[0] = x4537;
      extern_args[1] = x4538;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4539 = arg2[27 * steps + ((cycle - 0) & mask)];
      assert(x4539 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4540 = arg2[28 * steps + ((cycle - 0) & mask)];
      assert(x4540 != Fp::invalid());
      extern_args[0] = x4539;
      extern_args[1] = x4540;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4541 = arg2[29 * steps + ((cycle - 0) & mask)];
      assert(x4541 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4542 = arg2[30 * steps + ((cycle - 0) & mask)];
      assert(x4542 != Fp::invalid());
      extern_args[0] = x4541;
      extern_args[1] = x4542;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4543 = arg2[31 * steps + ((cycle - 0) & mask)];
      assert(x4543 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4544 = arg2[32 * steps + ((cycle - 0) & mask)];
      assert(x4544 != Fp::invalid());
      extern_args[0] = x4543;
      extern_args[1] = x4544;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4545 = arg2[33 * steps + ((cycle - 0) & mask)];
      assert(x4545 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4546 = arg2[34 * steps + ((cycle - 0) & mask)];
      assert(x4546 != Fp::invalid());
      extern_args[0] = x4545;
      extern_args[1] = x4546;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4547 = arg2[35 * steps + ((cycle - 0) & mask)];
      assert(x4547 != Fp::invalid());
      // loc("Top/mux(Mux)/body(BodyStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4548 = arg2[36 * steps + ((cycle - 0) & mask)];
      assert(x4548 != Fp::invalid());
      extern_args[0] = x4547;
      extern_args[1] = x4548;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
    }
  }
  if (x12 != 0) {
    {
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4549 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x4549 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4550 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x4550 != Fp::invalid());
      extern_args[0] = x4549;
      extern_args[1] = x4550;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4551 = arg2[5 * steps + ((cycle - 0) & mask)];
      assert(x4551 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4552 = arg2[6 * steps + ((cycle - 0) & mask)];
      assert(x4552 != Fp::invalid());
      extern_args[0] = x4551;
      extern_args[1] = x4552;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4553 = arg2[7 * steps + ((cycle - 0) & mask)];
      assert(x4553 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4554 = arg2[8 * steps + ((cycle - 0) & mask)];
      assert(x4554 != Fp::invalid());
      extern_args[0] = x4553;
      extern_args[1] = x4554;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4555 = arg2[9 * steps + ((cycle - 0) & mask)];
      assert(x4555 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4556 = arg2[10 * steps + ((cycle - 0) & mask)];
      assert(x4556 != Fp::invalid());
      extern_args[0] = x4555;
      extern_args[1] = x4556;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4557 = arg2[11 * steps + ((cycle - 0) & mask)];
      assert(x4557 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4558 = arg2[12 * steps + ((cycle - 0) & mask)];
      assert(x4558 != Fp::invalid());
      extern_args[0] = x4557;
      extern_args[1] = x4558;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4559 = arg2[13 * steps + ((cycle - 0) & mask)];
      assert(x4559 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4560 = arg2[14 * steps + ((cycle - 0) & mask)];
      assert(x4560 != Fp::invalid());
      extern_args[0] = x4559;
      extern_args[1] = x4560;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4561 = arg2[15 * steps + ((cycle - 0) & mask)];
      assert(x4561 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4562 = arg2[16 * steps + ((cycle - 0) & mask)];
      assert(x4562 != Fp::invalid());
      extern_args[0] = x4561;
      extern_args[1] = x4562;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4563 = arg2[17 * steps + ((cycle - 0) & mask)];
      assert(x4563 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4564 = arg2[18 * steps + ((cycle - 0) & mask)];
      assert(x4564 != Fp::invalid());
      extern_args[0] = x4563;
      extern_args[1] = x4564;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4565 = arg2[19 * steps + ((cycle - 0) & mask)];
      assert(x4565 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4566 = arg2[20 * steps + ((cycle - 0) & mask)];
      assert(x4566 != Fp::invalid());
      extern_args[0] = x4565;
      extern_args[1] = x4566;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4567 = arg2[21 * steps + ((cycle - 0) & mask)];
      assert(x4567 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4568 = arg2[22 * steps + ((cycle - 0) & mask)];
      assert(x4568 != Fp::invalid());
      extern_args[0] = x4567;
      extern_args[1] = x4568;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4569 = arg2[23 * steps + ((cycle - 0) & mask)];
      assert(x4569 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4570 = arg2[24 * steps + ((cycle - 0) & mask)];
      assert(x4570 != Fp::invalid());
      extern_args[0] = x4569;
      extern_args[1] = x4570;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4571 = arg2[25 * steps + ((cycle - 0) & mask)];
      assert(x4571 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4572 = arg2[26 * steps + ((cycle - 0) & mask)];
      assert(x4572 != Fp::invalid());
      extern_args[0] = x4571;
      extern_args[1] = x4572;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4573 = arg2[27 * steps + ((cycle - 0) & mask)];
      assert(x4573 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4574 = arg2[28 * steps + ((cycle - 0) & mask)];
      assert(x4574 != Fp::invalid());
      extern_args[0] = x4573;
      extern_args[1] = x4574;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4575 = arg2[29 * steps + ((cycle - 0) & mask)];
      assert(x4575 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4576 = arg2[30 * steps + ((cycle - 0) & mask)];
      assert(x4576 != Fp::invalid());
      extern_args[0] = x4575;
      extern_args[1] = x4576;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4577 = arg2[31 * steps + ((cycle - 0) & mask)];
      assert(x4577 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4578 = arg2[32 * steps + ((cycle - 0) & mask)];
      assert(x4578 != Fp::invalid());
      extern_args[0] = x4577;
      extern_args[1] = x4578;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4579 = arg2[33 * steps + ((cycle - 0) & mask)];
      assert(x4579 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4580 = arg2[34 * steps + ((cycle - 0) & mask)];
      assert(x4580 != Fp::invalid());
      extern_args[0] = x4579;
      extern_args[1] = x4580;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4581 = arg2[35 * steps + ((cycle - 0) & mask)];
      assert(x4581 != Fp::invalid());
      // loc("Top/mux(Mux)/ram_fini(RamFiniStep)/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./zirgen/compiler/edsl/component.h":164:27))
      auto x4582 = arg2[36 * steps + ((cycle - 0) & mask)];
      assert(x4582 != Fp::invalid());
      extern_args[0] = x4581;
      extern_args[1] = x4582;
      extern_plonkWrite_bytes(ctx, cycle, "bytes", extern_args, extern_outs);
    }
  }
}
